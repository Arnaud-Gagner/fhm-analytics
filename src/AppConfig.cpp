#include "AppConfig.h"

#include <mutex>
#include <toml/toml.h>

#include "wxNotifyUser.h"

namespace
{
    AppConfig_t Config;

    std::mutex Locker;
    const char* FILE_NAME = "general.toml";
    const char* FOLDER_PATH_KEY = "folder_path";
    const char* POSITION_THRESHOLD_KEY = "position_threshold";
}

AppConfig_t AppConfig::load()
{
    std::unique_lock<std::mutex> lock(Locker);
    toml::ParseResult tomlResult = toml::parse(std::ifstream(FILE_NAME));

    if (!tomlResult.valid()) {
        TERMINATE("Failed to read config file.");
    }
    const toml::Value& tomlValue = tomlResult.value;

    const toml::Value* pathToml = tomlValue.find(FOLDER_PATH_KEY);
    if (pathToml && pathToml->is<std::string>()) {
        Config.folderPath = pathToml->as<std::string>();
    }
    else {
        TERMINATE("Path configuration is not in string format. Please fix that.")
    }

    const toml::Value* positionThreshToml = tomlValue.find(POSITION_THRESHOLD_KEY);
    if (positionThreshToml && positionThreshToml->is<int>()) {
        Config.positionThreshold = positionThreshToml->as<int>();
    }
    else {
        TERMINATE("Path configuration is not in string format. Please fix that.")
    }
    return Config;
}

void AppConfig::save()
{
    std::unique_lock<std::mutex> lock(Locker);

    std::fstream file("general.toml");
    file << FOLDER_PATH_KEY << " = " << Config.folderPath << '\n';
    file << POSITION_THRESHOLD_KEY << " = " << Config.positionThreshold << '\n';
}

const AppConfig_t AppConfig::settings()
{
    std::unique_lock<std::mutex> lock(Locker);
    return Config;
}

void AppConfig::validate(const AppConfig_t& config) {}
