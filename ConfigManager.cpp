//
// Created by kychen on 25-7-11.
//

#include "ConfigManager.h"
#include "Header.h"

void ConfigManager::loadConfig(const std::string &filePath) {
    // 读取json文件,用json类型的变量Config接收
    // 载入默认配置
    // 使用 nlohmann::json 的 get_to() 或 get<>() 方法进行转换
    // Config.at("recentPaths").get_to(recentPaths);
    // 或者通过异常检测来实现类型的转换来成功获取recentPath数组
    }

void ConfigManager::saveConfig(const std::string &filePath) {
    // 获取当前的defaultPath、showHidden、recentPath存储进Config.json文件中
    // 用覆盖模式写入，以便于更新到最新的状态
    // 简单写入
    // ofs<<Config;
    // 格式化写入每行缩进两格
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
    // 长度检测，保证数组长度不超过5
}

void ConfigManager::setDefaultPath(const std::string &path) {
    defaultPath=path;
}

void ConfigManager::setShowHidden(const bool &val) {
    showHidden=val;
}
//测试用例1
//读取默认配置并输出
void test01() {
    ConfigManager manager;
    manager.loadConfig("Config.json");
    std::cout<<manager.getShowHidden()<<std::endl;
    std::cout<<manager.getDefaultPath()<<std::endl;
    for (const auto& path : manager.getRecentPaths()) {
        std::cout << "- " << path << std::endl;
    }
}
//测试用例2
//修改配置并输出检验是否修改成功
void test02() {
    ConfigManager manager;
    manager.loadConfig("Config.json");
    std::cout<<manager.getShowHidden()<<std::endl;
    std::cout<<manager.getDefaultPath()<<std::endl;
    //向空数组中添加
    manager.addRecentPath("/path1");
    manager.addRecentPath("/path2");
    manager.addRecentPath("/path3");
    manager.addRecentPath("/path4");
    for (const auto& path : manager.getRecentPaths()) {
        std::cout << "- " << path << std::endl;
    }
    manager.setDefaultPath("/D");
    manager.setShowHidden(false);
    std::cout<<manager.getShowHidden()<<std::endl;
    std::cout<<manager.getDefaultPath()<<std::endl;
    manager.saveConfig("Config.json");
}
