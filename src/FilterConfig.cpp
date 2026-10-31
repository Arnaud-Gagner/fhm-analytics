#include "FilterConfig.h"

#include <mutex>

#include "WxUtils.h"

namespace
{
    Filters_t Filters;
    u32 ActiveFilterIndex = 0;
    std::mutex Mutex;

    const char* FILE_NAME = "configs/filter.conf";
    const char* ACTIVE_FILTER_KEY = "active_filter";

    struct Buffer_t {
        char* data;
        u32 size;
    };

    Buffer_t takeLine(Buffer_t* buffer)
    {
        Buffer_t lineBuffer{ buffer->data, 0 };
        char* endOfLine = strchr(lineBuffer.data, '\n');
        buffer->size -= static_cast<u32>(endOfLine + 1 - buffer->data);
        buffer->data = endOfLine + 1;

        while (endOfLine - lineBuffer.data > 0 && *(endOfLine - 1) == ' '
               || *(endOfLine - 1) == '\t' || *(endOfLine - 1) == '\r') {
            --endOfLine;
        }
        lineBuffer.size = static_cast<u32>(endOfLine - lineBuffer.data);
        lineBuffer.data[lineBuffer.size] = '\0';
        return lineBuffer;
    }

    u32 findNextLineIndex(Buffer_t* buffer)
    {
        char* endOfLine = strchr(buffer->data, '\n');
        return static_cast<u32>(endOfLine + 1 - buffer->data);
    }

    void parseAge(Filter_t* filter, Buffer_t* line)
    {
        sscanf_s(line->data, "age %d %d", &filter->age[0], &filter->age[1]);
    }

    void parsePositions(Filter_t* filter, Buffer_t* line)
    {
        sscanf_s(line->data,
                 "position %u %u %u %u %u %u",
                 &filter->postions.g,
                 &filter->postions.ld,
                 &filter->postions.rd,
                 &filter->postions.lw,
                 &filter->postions.c,
                 &filter->postions.rw);
    }

    void parseLeagues(Filter_t* filter, Buffer_t* line) {}

    void parseStats(Filter_t* filter, Buffer_t* line) {}

    struct ParserDefinition_t {
        const char* keyName;
        void (*parser)(Filter_t* filter, Buffer_t* buffer);
    };

    constexpr ParserDefinition_t PARSER_DEFINITIONS[] = {
        {       "age",       parseAge },
        { "positions", parsePositions },
        {   "leagues",   parseLeagues },
        {      "stat",     parseStats }
    };

    void parseActiveFilter(Buffer_t* buffer, char (&name)[64])
    {
        name[0] = '\0';
        Buffer_t lineBuffer = takeLine(buffer);
        if (lineBuffer.size == 0) {
            TERMINATE("Filter Config couldn't find active filter");
        }
        if (sscanf_s(lineBuffer.data, "active_filter %63[^\n]", name, sizeof(name))
            != 1) {
            TERMINATE("Filter Config failed to extract active filter");
        }
    }

    Buffer_t takeFilter(Buffer_t* buffer)
    {
        Buffer_t filterBuffer = Buffer_t{ buffer->data, 0 };
        // TODO: find filter name line and start filling filterBuffer
        // TODO: find first empty line and (so the filter buffer size)
        return filterBuffer;
    }

    void interpretFilterBuffer(Buffer_t filterBuffer)
    {
        if (Filters.count >= Filters.capacity) {
            // TODO: realloc
        }
        Filter_t* filter = &Filters.items[Filters.count++];
        *filter = Filter_t{};
        // TODO
    }

    void updateFilterIndexFromName(char* name)
    {
        for (u32 i = 0; i < Filters.count; ++i) {
            if (strcmp(Filters.items[i].name, name) == 0) {
                ActiveFilterIndex = i;
                return;
            }
        }
        // TODO: add back
        // WARN("Couldn't find the active filter in the filters");
    }

    void parseBuffer(Buffer_t* buffer)
    {
        char activeFilterName[64];
        parseActiveFilter(buffer, activeFilterName);

        // TODO
        // while (buffer->size > 0) {
        //     Buffer_t filterBuffer = takeFilter(buffer);
        //     interpretFilterBuffer(filterBuffer);
        // }
        updateFilterIndexFromName(activeFilterName);
    }
}

void FilterConfig::load()
{
    std::unique_lock<std::mutex> lock(Mutex);
    FILE* file = fopen(FILE_NAME, "rb");
    if (!file) {
        TERMINATE("Failed to open filter file, verify it exists in path");
    }
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        TERMINATE("Failed to seek filter file");
    }
    long fileSize = ftell(file);
    if (fileSize < 0) {
        fclose(file);
        TERMINATE("Failed to determine filter file size");
    }
    rewind(file);

    u32 size = static_cast<u32>(fileSize);
    char* buffer = static_cast<char*>(malloc(size + 1));
    if (fread(buffer, 1, size, file) < size) {
        fclose(file);
        TERMINATE("Failed to read filter file.");
    }
    fclose(file);

    Buffer_t fileBuffer = Buffer_t{ buffer, size };
    fileBuffer.data[fileBuffer.size] = '\0';
    parseBuffer(&fileBuffer);
    free(buffer);
}

void FilterConfig::save(const Filter_t& filter)
{
    std::unique_lock<std::mutex> lock(Mutex);
}

void FilterConfig::create(const Filter_t& filter)
{
    std::unique_lock<std::mutex> lock(Mutex);
}

void FilterConfig::destroy(const Filter_t& filter)
{
    std::unique_lock<std::mutex> lock(Mutex);
}

void FilterConfig::modify(Filter_t& filter)
{
    std::unique_lock<std::mutex> lock(Mutex);
}

void FilterConfig::use(const char name[64])
{
    std::unique_lock<std::mutex> lock(Mutex);
}

Filter_t FilterConfig::filter(const char name[64])
{
    std::unique_lock<std::mutex> lock(Mutex);
    return Filter_t{};
}

Filter_t FilterConfig::activeFilter()
{
    std::unique_lock<std::mutex> lock(Mutex);
    return Filters.count == 0 || Filters.count <= ActiveFilterIndex
             ? Filter_t{}
             : Filters.items[ActiveFilterIndex];
}
