#include <ctype.h>
#include <string.h>
#define MAX_QUERY_WORDS 40
#define MAX_WORD_LENGTH 100

class TextProcessor {
public:
    static void process(const char* text, InvertedIndex* index,
                        Trie* trie, int documentId) {
        char word[MAX_WORD_LENGTH];
        int length = 0;
        for (int i = 0; ; i++) {
            unsigned char ch = (unsigned char)text[i];
            if (isalpha(ch)) {
                if (length < MAX_WORD_LENGTH - 1)
                    word[length++] = (char)tolower(ch);
            } else {
                if (length > 0) {
                    word[length] = '\0';
                    index->add(word, documentId);
                    trie->insert(word);
                    length = 0;
                }
                if (text[i] == '\0') break;
            }
        }
    }

    static int getWords(const char* text,
                        char words[MAX_QUERY_WORDS][MAX_WORD_LENGTH]) {
        int count = 0, length = 0;
        char word[MAX_WORD_LENGTH];
        for (int i = 0; ; i++) {
            unsigned char ch = (unsigned char)text[i];
            if (isalpha(ch)) {
                if (length < MAX_WORD_LENGTH - 1)
                    word[length++] = (char)tolower(ch);
            } else {
                if (length > 0 && count < MAX_QUERY_WORDS) {
                    word[length] = '\0';
                    strcpy(words[count++], word);
                    length = 0;
                }
                if (text[i] == '\0') break;
            }
        }
        return count;
    }
};
