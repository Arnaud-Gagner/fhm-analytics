#include "CsvUtils.h"

#include <cstdio>
#include <cstdlib>

#include "wxUtils.h"

void CsvUtils::load(const char* filePath, char** buffer, size_t& size)
{
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        TERMINATE("Failed to open CSV file, verify it exists in path");
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        TERMINATE("Failed to seek CSV file");
    }

    long fileSize = ftell(file);
    if (fileSize < 0) {
        TERMINATE("Failed to determine CSV file size");
    }
    rewind(file);

    size = static_cast<size_t>(fileSize);
    *buffer = static_cast<char*>(malloc(size + 1));
    if (fread(*buffer, 1, size, file) < size) {
        TERMINATE("buffer L");
    }
}
