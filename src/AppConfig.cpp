#include "AppConfig.h"

#include <mutex>
#include <toml/toml.h>

#include "wxNotifyUser.h"

namespace
{
    AppConfig_t Config;
    std::mutex Locker;

    const char* FILE_NAME = "configs/general.toml";

    const char* FOLDER_PATH_KEY = "folder_path";
    const char* CSV_SEPARATOR_KEY = "csv_separator";
    const char* POSITION_THRESHOLD_KEY = "position_threshold";
}

void AppConfig::load()
{
    std::unique_lock<std::mutex> lock(Locker);
    std::ifstream file(FILE_NAME);
    toml::ParseResult tomlResult = toml::parse(file);

    if (!tomlResult.valid()) {
        TERMINATE("Failed to read config file.");
    }
    const toml::Value& tomlValue = tomlResult.value;

    const toml::Value* pathToml = tomlValue.find(FOLDER_PATH_KEY);
    if (!pathToml || !pathToml->is<std::string>()) {
        TERMINATE("Path configuration is not in string format. Please fix that.")
    }
    Config.folderPath = pathToml->as<std::string>();

    const toml::Value* separatorToml = tomlValue.find(CSV_SEPARATOR_KEY);
    if (!separatorToml || !separatorToml->is<std::string>()) {
        TERMINATE("Path configuration is not in string format. Please fix that.")
    }
    if (separatorToml->as<std::string>() == "") {
        TERMINATE("No values for CSV separator in configs.")
    }
    Config.csvSeparator = separatorToml->as<std::string>()[0];

    const toml::Value* positionThreshToml = tomlValue.find(POSITION_THRESHOLD_KEY);
    if (!positionThreshToml || !positionThreshToml->is<int>()) {
        TERMINATE("Path configuration is not in string format. Please fix that.")
    }
    Config.positionThreshold = positionThreshToml->as<int>();
}

void AppConfig::save()
{
    std::unique_lock<std::mutex> lock(Locker);

    std::fstream file(FILE_NAME);
    file << FOLDER_PATH_KEY << " = \"" << Config.folderPath << "\"\n";
    file << CSV_SEPARATOR_KEY << " = \"" << Config.csvSeparator << "\"\n";
    file << POSITION_THRESHOLD_KEY << " = " << Config.positionThreshold << '\n';
}

const AppConfig_t AppConfig::settings()
{
    std::unique_lock<std::mutex> lock(Locker);
    return Config;
}

void AppConfig::validate(const AppConfig_t& config)
{
    if (config.positionThreshold < 0 || config.positionThreshold > 20) {
        WARN("Position Threshold should be between 0 and 20 (included).");
    }
    {
        std::unique_lock<std::mutex> lock(Locker);
        Config = config;
    }
    save();
}
