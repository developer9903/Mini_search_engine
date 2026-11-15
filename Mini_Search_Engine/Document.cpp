#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILENAME 260

class Document {
public:
    int id;
    char filename[MAX_FILENAME];
    char* content;

    Document() : id(0), content(NULL) { filename[0] = '\0'; }

    ~Document() {
        if (content != NULL) free(content);
    }

    bool loadFromFile(int documentId, const char* path, const char* shortName) {
        FILE* file = fopen(path, "rb");
        if (file == NULL) return false;
        if (fseek(file, 0, SEEK_END) != 0) { fclose(file); return false; }
        long size = ftell(file);
        if (size < 0) { fclose(file); return false; }
        rewind(file);

        char* buffer = (char*)malloc((size_t)size + 1);
        if (buffer == NULL) { fclose(file); return false; }
        size_t count = fread(buffer, 1, (size_t)size, file);
        buffer[count] = '\0';
        fclose(file);

        if (content != NULL) free(content);
        content = buffer;
        id = documentId;
        strncpy(filename, shortName, MAX_FILENAME - 1);
        filename[MAX_FILENAME - 1] = '\0';
        return true;
    }
};
