MINI SEARCH ENGINE

Project files:
- main.cpp: main() and includes all class implementation files.
- Document.cpp: Document class and FILE* text-file loading.
- Trie.cpp: TrieNode and Trie classes for autocomplete.
- InvertedIndex.cpp: hash table, IndexEntry.
- TextProcessor.cpp: tokenization, lowercase conversion.
- SearchEngine.cpp: document loading, searching, ranking and menu operations.
- docs/: sample .txt documents.

The program uses C-style arrays, pointers, structs, classes, dynamic allocation,
FILE* and platform folder scanning.

IMPORTANT:
Compile ONLY main.cpp because it includes the other .cpp files:
  g++ -std=c++11 -O2 -Wall -Wextra main.cpp -o mini_search.exe

Windows folder scanning uses windows.h APIs.
Linux folder scanning uses dirent.h APIs.
