/*
 MINI SEARCH ENGINE - NO STL, NO CUSTOM HEADER FILES
 Compile ONLY this file:
 g++ -std=c++11 -O2 -Wall -Wextra main.cpp -o mini_search.exe
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100
#define MAX_SUGGESTIONS 50
#define MAX_QUERY_WORDS 40

// Include .cpp class files in dependency order.
// Do not separately compile these included .cpp files.
#include "Document.cpp"
#include "Trie.cpp"
#include "InvertedIndex.cpp"
#include "TextProcessor.cpp"
#include "SearchEngine.cpp"

int main(int argc, char* argv[]) {
    const char* folder = (argc > 1) ? argv[1] : "docs";
    printf("====================================\n");
    printf("       MINI SEARCH ENGINE (C++)\n");
    printf("====================================\n");
    printf("Loading .txt files from: %s\n", folder);

    SearchEngine engine;
    if (!engine.loadDocuments(folder)) {
        printf("Put .txt files inside the docs folder.\n");
        return 1;
    }
    engine.listDocuments();

    int choice = 0;
    char input[1000];
    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Search documents\n");
        printf("2. Autocomplete a word\n");
        printf("3. List documents\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) return 0;
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) { }

        if (choice == 1) {
            printf("Enter search query: ");
            if (fgets(input, sizeof(input), stdin)) {
                input[strcspn(input, "\r\n")] = '\0';
                engine.search(input);
            }
        } else if (choice == 2) {
            printf("Enter prefix: ");
            if (fgets(input, sizeof(input), stdin)) {
                input[strcspn(input, "\r\n")] = '\0';
                engine.autocomplete(input);
            }
        } else if (choice == 3) {
            engine.listDocuments();
        } else if (choice == 4) {
            printf("Goodbye!\n");
        } else {
            printf("Invalid choice.\n");
        }
    } while (choice != 4);
    return 0;
}
