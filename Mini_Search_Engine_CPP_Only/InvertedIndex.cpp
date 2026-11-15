#include <string.h>
#define MAX_WORD_LENGTH 100
#define HASH_BUCKETS 1009

struct PostingNode {
    int documentId;
    int frequency;
    PostingNode* next;
    PostingNode(int id) : documentId(id), frequency(1), next(NULL) {}
};

struct IndexEntry {
    char word[MAX_WORD_LENGTH];
    PostingNode* postings;
    IndexEntry* next;
    IndexEntry(const char* value) : postings(NULL), next(NULL) {
        strncpy(word, value, MAX_WORD_LENGTH - 1);
        word[MAX_WORD_LENGTH - 1] = '\0';
    }
    ~IndexEntry() {
        PostingNode* p = postings;
        while (p) {
            PostingNode* nextNode = p->next;
            delete p;
            p = nextNode;
        }
    }
};

class InvertedIndex {
private:
    IndexEntry* buckets[HASH_BUCKETS];
    unsigned int hashWord(const char* word) {
        unsigned int hash = 0;
        for (int i = 0; word[i]; i++)
            hash = (hash * 31u + (unsigned char)word[i]) % HASH_BUCKETS;
        return hash;
    }
    IndexEntry* findEntry(const char* word) {
        IndexEntry* p = buckets[hashWord(word)];
        while (p) {
            if (strcmp(p->word, word) == 0) return p;
            p = p->next;
        }
        return NULL;
    }
public:
    InvertedIndex() {
        for (int i = 0; i < HASH_BUCKETS; i++) buckets[i] = NULL;
    }
    ~InvertedIndex() {
        for (int i = 0; i < HASH_BUCKETS; i++) {
            IndexEntry* p = buckets[i];
            while (p) {
                IndexEntry* nextEntry = p->next;
                delete p;
                p = nextEntry;
            }
        }
    }
    void add(const char* word, int documentId) {
        if (!word || !word[0]) return;
        unsigned int b = hashWord(word);
        IndexEntry* entry = findEntry(word);
        if (!entry) {
            entry = new IndexEntry(word);
            entry->next = buckets[b];
            buckets[b] = entry;
        }
        PostingNode* p = entry->postings;
        while (p) {
            if (p->documentId == documentId) { p->frequency++; return; }
            p = p->next;
        }
        PostingNode* added = new PostingNode(documentId);
        added->next = entry->postings;
        entry->postings = added;
    }
    PostingNode* getPostings(const char* word) {
        IndexEntry* entry = findEntry(word);
        return entry ? entry->postings : NULL;
    }
};
