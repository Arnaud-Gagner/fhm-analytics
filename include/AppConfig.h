#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <functional>
#include <string>

struct AppConfig_t {
    std::string folderPath = "";
    char csvSeparator = ';';
    int positionThreshold = 15;
};

namespace AppConfig
{
    void load();
    void save();

    const AppConfig_t settings();
    void validate(const AppConfig_t& config);

    void setCallback(const std::function<void(const AppConfig_t&)>& callback);
};

#endif // !APP_CONFIG_H
