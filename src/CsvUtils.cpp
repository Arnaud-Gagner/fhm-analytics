#include "CsvUtils.h"

#include <cstdio>
#include <cstdlib>

#include "wxUtils.h"

namespace
{
    bool infoLine(char* buffer, char* fields[14])
    {
        fields[0] = buffer;
        size_t fieldIndex = 0;

        for (size_t i = 0; i < 512; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                buffer[i] == '\0';
                return fieldIndex == 14;
            }
            if (buffer[i] == ';') {
                buffer[i] = '\0';
                fieldIndex++;
                fields[fieldIndex] = &buffer[i + 1];
            }
        }
        return true;
    }

    void deserializeInfo(Player_t& player, char* fields[14])
    {
        player.id = atoi(fields[0]);
        strncpy(player.info.firstName, fields[3], sizeof(player.info.firstName) - 1);
        strncpy(player.info.lastName, fields[4], sizeof(player.info.lastName) - 1);
        strncpy(player.info.birthDate, fields[8], sizeof(player.info.birthDate) - 1);
    }
}

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
        TERMINATE("Failed to read CSV file.");
    }
}

void CsvUtils::interpretMaster(std::vector<Player_t>& players,
                               const char* buffer,
                               size_t size)
{
    size_t bufferIndex = strchr(buffer, '\n') - buffer;

    bool isFileFinished = false;
    while (!isFileFinished) {
        Player_t player{};
        char line[512] = {};

        const char* ptrPosition = strchr(buffer + bufferIndex, '\n') + 1;
        const char* ptrEndl = strchr(ptrPosition, '\n');
        if (!ptrEndl) {
            return;
        }
        std::memcpy(&line, ptrPosition, ptrEndl - ptrPosition + 1);
        line[511] = '\0';

        char* fields[15] = {};
        if (infoLine(line, fields)) {
            deserializeInfo(player, fields);
            players.push_back(std::move(player));
        }
        bufferIndex = ptrPosition - buffer;
        isFileFinished = bufferIndex + 1 >= size;
    }
}

void CsvUtils::interpretRatings(const char* buffer, size_t size) {}

void CsvUtils::interpretSats(const char* buffer, size_t size) {}
