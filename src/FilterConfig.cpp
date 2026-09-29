#include "FilterConfig.h"

#include <mutex>

namespace
{
    Filter_t ActiveFilter{};
    std::mutex Mutex;
}

void FilterConfig::load()
{
    std::unique_lock<std::mutex> lock(Mutex);
}

Filter_t FilterConfig::filter()
{
    std::unique_lock<std::mutex> lock(Mutex);
    return ActiveFilter;
}
