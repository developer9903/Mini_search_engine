MINI SEARCH ENGINE - CPP ONLY, NO STL, NO .h FILES

Project files:
- main.cpp: main() and includes all class implementation files.
- Document.cpp: Document class and FILE* text-file loading.
- Trie.cpp: TrieNode and Trie classes for autocomplete.
- InvertedIndex.cpp: hash table, IndexEntry and linked-list postings.
- TextProcessor.cpp: tokenization, lowercase conversion and query parsing.
- SearchEngine.cpp: document loading, searching, ranking and menu operations.
- docs/: sample .txt documents.

No custom .h files are used. No STL containers or algorithms are used.
The program uses C-style arrays, pointers, structs, classes, dynamic allocation,
FILE* and platform folder scanning.

IMPORTANT:
Compile ONLY main.cpp because it includes the other .cpp files:
  g++ -std=c++11 -O2 -Wall -Wextra main.cpp -o mini_search.exe

Do NOT compile every .cpp file in one command; that would duplicate definitions.
Run from this project folder so that the docs folder is found.

Windows folder scanning uses windows.h APIs.
Linux folder scanning uses dirent.h APIs.
