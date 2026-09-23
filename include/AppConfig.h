#ifndef APP_CONFIG_H
#define APP_CONFIG_H

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
};

#endif // !APP_CONFIG_H
