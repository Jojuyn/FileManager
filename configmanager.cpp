#include "configmanager.h"
#include <fstream>
#include <QCoreApplication>
#include <QDir>

void ConfigManager::loadConfig(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        try {
            Config = nlohmann::json::parse(file);
            defaultPath = Config.value("defaultPath", "");
            showHidden = Config.value("showHidden", true);
            recentPaths = Config.value("recentPaths", std::vector<std::string>());
            fileFilterExtension = Config.value("fileFilterExtension", std::vector<std::string>());
            Theme = Config.value("Theme", "default");
        } catch (const nlohmann::json::exception& e) {
            defaultPath = "";
            showHidden = true;
            recentPaths.clear();
            fileFilterExtension.clear();
            Theme = "default";
        }
        file.close();
    }
}

void ConfigManager::saveConfig(const std::string& filePath) {
    Config["defaultPath"] = defaultPath;
    Config["showHidden"] = showHidden;
    Config["recentPaths"] = recentPaths;
    Config["fileFilterExtension"] = fileFilterExtension;
    Config["Theme"] = Theme;

    std::ofstream file(filePath);
    if (file.is_open()) {
        file << Config.dump(4);
        file.close();
    }
}

std::string ConfigManager::getDefaultPath() const {
    return defaultPath;
}

bool ConfigManager::getShowHidden() const {
    return showHidden;
}

std::vector<std::string> ConfigManager::getRecentPaths() const {
    return recentPaths;
}


void ConfigManager::addRecentPath(const std::string &path) {
    if (recentPaths.size() <= 5) {
        // 避免重复添加
        if (std::find(recentPaths.begin(), recentPaths.end(), path) == recentPaths.end()) {
            recentPaths.push_back(path);
        }
    }
}

void ConfigManager::clearRecentPath() {
    recentPaths.clear();
}

void ConfigManager::setDefaultPath(const std::string& path) {
    defaultPath = path;
}

void ConfigManager::setShowHidden(const bool &val) {
    showHidden = val;
}

void ConfigManager::setTheme(const std::string &theme) {
    Theme = theme;
}

std::string ConfigManager::getTheme() const {
    return Theme;
}

void ConfigManager::setFileFilter(const std::vector<std::string> &fileFilter) {
    fileFilterExtension = fileFilter;
}

std::vector<std::string> ConfigManager::getFileFilter() const {
    return fileFilterExtension;
}

void ConfigManager::addfileFilter(const std::string &fileExtension) {
    if (std::find(fileFilterExtension.begin(), fileFilterExtension.end(), fileExtension) == fileFilterExtension.end()) {
        fileFilterExtension.push_back(fileExtension);
    }
}

void ConfigManager::clearFileFilter() {
    fileFilterExtension.clear();
}
