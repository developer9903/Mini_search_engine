#include <string.h>
#define MAX_WORD_LENGTH 100
#define MAX_SUGGESTIONS 50

class TrieNode {
public:
    TrieNode* children[26];
    bool endOfWord;
    TrieNode() : endOfWord(false) {
        for (int i = 0; i < 26; i++) children[i] = NULL;
    }
    ~TrieNode() {
        for (int i = 0; i < 26; i++) if (children[i]) delete children[i];
    }
};

class Trie {
private:
    TrieNode* root;
    void collect(TrieNode* node, char* word, int depth, int& count,
                 char output[MAX_SUGGESTIONS][MAX_WORD_LENGTH]) {
        if (!node || count >= MAX_SUGGESTIONS || depth >= MAX_WORD_LENGTH - 1) return;
        if (node->endOfWord) {
            word[depth] = '\0';
            strcpy(output[count++], word);
        }
        for (int i = 0; i < 26 && count < MAX_SUGGESTIONS; i++) {
            if (node->children[i]) {
                word[depth] = (char)('a' + i);
                collect(node->children[i], word, depth + 1, count, output);
            }
        }
    }
public:
    Trie() { root = new TrieNode(); }
    ~Trie() { delete root; }
    void insert(const char* word) {
        if (!word || !word[0]) return;
        TrieNode* current = root;
        for (int i = 0; word[i]; i++) {
            if (word[i] < 'a' || word[i] > 'z') return;
            int p = word[i] - 'a';
            if (!current->children[p]) current->children[p] = new TrieNode();
            current = current->children[p];
        }
        current->endOfWord = true;
    }
    int autocomplete(const char* prefix,
                     char output[MAX_SUGGESTIONS][MAX_WORD_LENGTH]) {
        if (!prefix || !prefix[0]) return 0;
        TrieNode* current = root;
        for (int i = 0; prefix[i]; i++) {
            if (prefix[i] < 'a' || prefix[i] > 'z') return 0;
            int p = prefix[i] - 'a';
            if (!current->children[p]) return 0;
            current = current->children[p];
        }
        char word[MAX_WORD_LENGTH];
        strncpy(word, prefix, MAX_WORD_LENGTH - 1);
        word[MAX_WORD_LENGTH - 1] = '\0';
        int count = 0;
        collect(current, word, (int)strlen(word), count, output);
        return count;
    }
};
