#include "FilterConfig.h"

#include <mutex>

#include "WxUtils.h"

namespace
{
    Filter_t ActiveFilter{};
    std::mutex Mutex;

    const char* FILE_NAME = "configs/filter.conf";
    const char* ACTIVE_FILTER_KEY = "active_filter";
}

void FilterConfig::load() {}

void FilterConfig::save(const Filter_t& filter)
{
    std::unique_lock<std::mutex> lock(Mutex);
}

void FilterConfig::create(const Filter_t& filter)
{
    // TODO: save a new filter
}

void FilterConfig::destroy(const Filter_t& filter) {}

void FilterConfig::modify(Filter_t& filter) {}

void FilterConfig::use(const char name[64]) {}

Filter_t FilterConfig::filter(const char name[64]) {}

Filter_t FilterConfig::activeFilter()
{
    std::unique_lock<std::mutex> lock(Mutex);
    return ActiveFilter;
}
