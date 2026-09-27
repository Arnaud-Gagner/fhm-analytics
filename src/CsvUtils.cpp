#include "CsvUtils.h"

#include <cstdio>
#include <cstdlib>

#include "wxUtils.h"

namespace
{
    bool teamLine(char* buffer, i32& teamId, i16& leagueId)
    {
        char* text = buffer;
        int cnt = 0;
        for (size_t i = 0; i < 512; ++i) {
            if (buffer[i] == ';') {
                buffer[i] = '\0';
                if (cnt == 0) {
                    teamId = std::atoi(text);
                    cnt++;
                    text = &buffer[i + 1];
                }
                else {
                    leagueId = std::atoi(text);
                    return true;
                }
            }
        }
        return true;
    }

    bool infoLine(char* buffer, char* fields[15])
    {
        fields[0] = buffer;
        size_t fieldIndex = 0;

        for (size_t i = 0; i < 512; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                buffer[i] == '\0';
                return fieldIndex == 14;
            }
            if (buffer[i] == ';' && fieldIndex <= 13) {
                buffer[i] = '\0';
                fieldIndex++;
                fields[fieldIndex] = &buffer[i + 1];
            }
            else if (buffer[i] == ';' && fieldIndex > 14) {
                buffer[i] = '\0';
                return false;
            }
        }
        return true;
    }

    void deserializeInfo(Player_t& player, char* fields[15])
    {
        player.info.id = atoi(fields[0]);
        player.info.teamId = atoi(fields[1]);
        strncpy(player.info.firstName, fields[3], sizeof(player.info.firstName) - 1);
        strncpy(player.info.lastName, fields[4], sizeof(player.info.lastName) - 1);
        strncpy(player.info.birthDate, fields[8], sizeof(player.info.birthDate) - 1);
    }

    bool ratingsLine(char* buffer, char* fields[58])
    {
        // TODO: skips line when got all the positions data
        fields[0] = buffer;
        size_t fieldIndex = 0;

        for (size_t i = 0; i < 512; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                buffer[i] == '\0';
                return fieldIndex == 57;
            }
            if (buffer[i] == ';' && fieldIndex <= 56) {
                buffer[i] = '\0';
                fieldIndex++;
                fields[fieldIndex] = &buffer[i + 1];
            }
            else if (buffer[i] == ';' && fieldIndex > 57) {
                buffer[i] = '\0';
                return false;
            }
        }
        return true;
    }

    void deserializeRatings(Player_t& player, char* fields[58])
    {
        player.position.g = std::atoi(fields[1]);
        player.position.ld = std::atoi(fields[2]);
        player.position.rd = std::atoi(fields[3]);
        player.position.lw = std::atoi(fields[4]);
        player.position.c = std::atoi(fields[5]);
        player.position.rw = std::atoi(fields[6]);
    }

    bool statsLine(char* buffer, char* fields[41])
    {
        fields[0] = buffer;
        size_t fieldIndex = 0;

        for (size_t i = 0; i < 512; ++i) {
            if (buffer[i] == '\n' || buffer[i] == '\0') {
                buffer[i] == '\0';
                return fieldIndex == 40;
            }
            if (buffer[i] == ';' && fieldIndex <= 39) {
                buffer[i] = '\0';
                fieldIndex++;
                fields[fieldIndex] = &buffer[i + 1];
            }
            else if (buffer[i] == ';' && fieldIndex > 40) {
                buffer[i] = '\0';
                return false;
            }
        }
        return true;
    }

    void deserializeStats(Player_t& player, char* fields[41])
    {
        player.stat.gp = atoi(fields[3]);
        player.stat.goals = atoi(fields[4]);
        player.stat.assists = atoi(fields[5]);
        player.stat.plusMinus = atoi(fields[6]);
        player.stat.pim = atoi(fields[7]);
        player.stat.ppg = atoi(fields[8]);
        player.stat.ppa = atoi(fields[9]);
        player.stat.shg = atoi(fields[10]);
        player.stat.sha = atoi(fields[11]);
        player.stat.fight = atoi(fields[12]);
        player.stat.fightWon = atoi(fields[13]);
        player.stat.hits = atoi(fields[14]);
        player.stat.gva = atoi(fields[15]);
        player.stat.tka = atoi(fields[16]);
        player.stat.sb = atoi(fields[17]);
        player.stat.shots = atoi(fields[21]);
        player.stat.toi = atoi(fields[22]);
        player.stat.pptoi = atoi(fields[23]);
        player.stat.shtoi = atoi(fields[24]);
        player.stat.pdo = atof(fields[25]);
        player.stat.gf60 = atof(fields[26]);
        player.stat.ga60 = atof(fields[27]);
        player.stat.sf60 = atof(fields[28]);
        player.stat.sa60 = atof(fields[29]);
        player.stat.cf = atof(fields[30]);
        player.stat.ca = atof(fields[31]);
        player.stat.cfPer = atof(fields[32]);
        player.stat.cfRel = atof(fields[33]);
        player.stat.gwg = atoi(fields[38]);
        player.stat.fo = atoi(fields[39]);
        player.stat.fow = atoi(fields[40]);
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

void CsvUtils::interpretTeam(Teams_t& teams, const char* buffer, size_t size)
{
    // TODO: avoid vector or at least reserve place
    // TODO: avoid creating a copy of a lines
    teams.insert_or_assign(-1, -1);
    size_t bufferIndex = strchr(buffer, '\n') - buffer;

    bool isFileFinished = false;
    while (!isFileFinished) {
        char line[512] = {};

        const char* ptrPosition = strchr(buffer + bufferIndex, '\n') + 1;
        const char* ptrEndl = strchr(ptrPosition, '\n');
        if (!ptrEndl) {
            return;
        }
        std::memcpy(&line, ptrPosition, ptrEndl - ptrPosition + 1);
        line[511] = '\0';

        i32 teamId = 0;
        i16 leagueId = 0;
        if (teamLine(line, teamId, leagueId)) {
            teams.insert_or_assign(teamId, leagueId);
        }
        bufferIndex = ptrPosition - buffer;
        isFileFinished = bufferIndex + 1 >= size;
    }
}

void CsvUtils::interpretMaster(const Teams_t& teams,
                               Players_t& players,
                               const char* buffer,
                               size_t size)
{
    // TODO: avoid vector or at least reserve place
    // TODO: avoid creating a copy of a lines
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

        char* fields[58] = {};
        if (infoLine(line, fields)) {
            deserializeInfo(player, fields);
            player.info.leagueId = teams.at(player.info.teamId);
            players.insert_or_assign(player.info.id, player);
        }
        bufferIndex = ptrPosition - buffer;
        isFileFinished = bufferIndex + 1 >= size;
    }
}

void CsvUtils::interpretRatings(Players_t& players, const char* buffer, size_t size)
{
    // TODO: avoid vector or at least reserve place
    // TODO: avoid creating a copy of a lines
    size_t bufferIndex = strchr(buffer, '\n') - buffer;

    bool isFileFinished = false;
    while (!isFileFinished) {
        char line[512] = {};

        const char* ptrPosition = strchr(buffer + bufferIndex, '\n') + 1;
        const char* ptrEndl = strchr(ptrPosition, '\n');
        if (!ptrEndl) {
            return;
        }
        std::memcpy(&line, ptrPosition, ptrEndl - ptrPosition + 1);
        line[511] = '\0';

        char* fields[15] = {};
        if (ratingsLine(line, fields)) {
            deserializeRatings(players[std::atoi(fields[0])], fields);
        }
        bufferIndex = ptrPosition - buffer;
        isFileFinished = bufferIndex + 1 >= size;
    }
}

void CsvUtils::interpretStats(Players_t& players, const char* buffer, size_t size)
{
    // TODO: avoid vector or at least reserve place
    // TODO: avoid creating a copy of a lines
    size_t bufferIndex = strchr(buffer, '\n') - buffer;

    bool isFileFinished = false;
    while (!isFileFinished) {
        char line[512] = {};

        const char* ptrPosition = strchr(buffer + bufferIndex, '\n') + 1;
        const char* ptrEndl = strchr(ptrPosition, '\n');
        if (!ptrEndl) {
            return;
        }
        std::memcpy(&line, ptrPosition, ptrEndl - ptrPosition + 1);
        line[511] = '\0';

        char* fields[41] = {};
        if (statsLine(line, fields)) {
            deserializeStats(players[std::atoi(fields[0])], fields);
        }
        bufferIndex = ptrPosition - buffer;
        isFileFinished = bufferIndex + 1 >= size;
    }
}
