#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif

#define MAX_DOCUMENTS 100
#define MAX_PATH_LENGTH 520

class SearchEngine {
private:
    Document documents[MAX_DOCUMENTS];
    int documentCount;
    InvertedIndex index;
    Trie vocabulary;

    int findDocumentPosition(int id) {
        for (int i = 0; i < documentCount; i++)
            if (documents[i].id == id) return i;
        return -1;
    }

    bool isTxtFile(const char* name) {
        size_t n = strlen(name);
        return n >= 4 && (strcmp(name + n - 4, ".txt") == 0 ||
                          strcmp(name + n - 4, ".TXT") == 0);
    }

    bool addDocument(const char* folder, const char* name) {
        if (documentCount >= MAX_DOCUMENTS || !isTxtFile(name)) return false;
        char path[MAX_PATH_LENGTH];
#ifdef _WIN32
        snprintf(path, sizeof(path), "%s\\%s", folder, name);
#else
        snprintf(path, sizeof(path), "%s/%s", folder, name);
#endif
        int id = documentCount + 1;
        if (!documents[documentCount].loadFromFile(id, path, name)) return false;
        TextProcessor::process(documents[documentCount].content, &index, &vocabulary, id);
        documentCount++;
        return true;
    }

public:
    SearchEngine() : documentCount(0) {}

    bool loadDocuments(const char* folder) {
        int loaded = 0;
#ifdef _WIN32
        char pattern[MAX_PATH_LENGTH];
        snprintf(pattern, sizeof(pattern), "%s\\*.txt", folder);
        WIN32_FIND_DATAA data;
        HANDLE h = FindFirstFileA(pattern, &data);
        if (h == INVALID_HANDLE_VALUE) {
            printf("Folder '%s' not found or contains no .txt files.\n", folder);
            return false;
        }
        do {
            if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                if (addDocument(folder, data.cFileName)) loaded++;
        } while (FindNextFileA(h, &data));
        FindClose(h);
#else
        DIR* dir = opendir(folder);
        if (!dir) {
            printf("Folder '%s' not found.\n", folder);
            return false;
        }
        struct dirent* item;
        while ((item = readdir(dir)) != NULL) {
            if (item->d_type != DT_DIR)
                if (addDocument(folder, item->d_name)) loaded++;
        }
        closedir(dir);
#endif
        if (!loaded) {
            printf("No .txt files loaded from '%s'.\n", folder);
            return false;
        }
        return true;
    }

    void listDocuments() {
        printf("\nIndexed documents:\n");
        for (int i = 0; i < documentCount; i++)
            printf("[%d] %s\n", documents[i].id, documents[i].filename);
    }

    void search(const char* query) {
        char words[MAX_QUERY_WORDS][MAX_WORD_LENGTH];
        int count = TextProcessor::getWords(query, words);
        if (!count) { printf("Enter a valid query.\n"); return; }

        int scores[MAX_DOCUMENTS] = {0};
        for (int w = 0; w < count; w++) {
            PostingNode* p = index.getPostings(words[w]);
            while (p) {
                int position = findDocumentPosition(p->documentId);
                if (position >= 0) scores[position] += p->frequency;
                p = p->next;
            }
        }

        bool printed[MAX_DOCUMENTS] = {false};
        int resultCount = 0;
        printf("\nResults for: %s\n", query);
        while (true) {
            int best = -1, bestScore = 0;
            for (int i = 0; i < documentCount; i++)
                if (!printed[i] && scores[i] > bestScore) {
                    best = i;
                    bestScore = scores[i];
                }
            if (best == -1) break;
            printed[best] = true;
            printf("%d. %s (score: %d)\n", ++resultCount,
                   documents[best].filename, bestScore);
        }
        if (!resultCount) printf("No matching documents found.\n");
    }

    void autocomplete(const char* input) {
        char words[MAX_QUERY_WORDS][MAX_WORD_LENGTH];
        int count = TextProcessor::getWords(input, words);
        if (!count) { printf("Enter a prefix using letters.\n"); return; }

        char suggestions[MAX_SUGGESTIONS][MAX_WORD_LENGTH];
        int found = vocabulary.autocomplete(words[count - 1], suggestions);
        if (!found) { printf("No suggestions found.\n"); return; }
        printf("Suggestions:\n");
        for (int i = 0; i < found; i++) printf("- %s\n", suggestions[i]);
    }
};
