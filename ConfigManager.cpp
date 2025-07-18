//
// Created by kychen on 25-7-11.
//

#include "ConfigManager.h"
#include "Header.h"

void ConfigManager::loadConfig(const std::string &filePath) {
    //读取json文件,用json类型的变量Config接收
    std::ifstream ifs;
    ifs.open(filePath);
    if (!ifs.is_open()) {
        std::cerr<<"File open failed"<<std::endl;
        return;
    }
    ifs>>Config;
    ifs.close();
    defaultPath=Config["defaultPath"];
    showHidden=Config["showHidden"];
    //recentPaths=Config["recentPath"];
    // 使用 nlohmann::json 的 get_to() 或 get<>() 方法进行转换
    //Config.at("recentPaths").get_to(recentPaths);
    // 或者
     try {
            // 1. 检查键是否存在
            if (Config.contains("recentPaths")) {
                // 2. 检查类型是否为数组
                if (Config["recentPaths"].is_array()) {
                    // 尝试获取数组，这里可能会抛出异常如果数组内元素类型不匹配
                    recentPaths = Config["recentPaths"].get<std::vector<std::string>>();
                    std::cout << "Successfully obtained recentPaths, size: " << recentPaths.size() << std::endl;
                    //载入内存后将历史路径记录进行输出
                    // for (const auto& path : recentPaths) {
                    //     std::cout << "- " << path << std::endl;
                    // }
                } else if (Config["recentPaths"].is_null()) {
                    // 如果是 null，可以将其视为空数组
                    std::cout << "recentPath exists but is null, it will be initialized as an empty vector." << std::endl;
                    recentPaths.clear();
                } else {
                    // 类型不匹配，例如是字符串、数字、对象等
                    std::cerr << "Error: recentPath exists but is not of array type! The actual type is: "
                              << Config["recentPaths"].type_name() << std::endl;
                    recentPaths.clear();
                }
            } else {
                // 键不存在，初始化为空数组
                std::cout << "recentPath does not exist, it will be initialized as an empty vector." << std::endl;
                recentPaths.clear();
            }
        } catch (const nlohmann::json::type_error& e) {
            // 捕获 nlohmann::json::type_error 异常
            std::cerr << "Capture JSON type error: " << e.what() << std::endl;
            std::cerr << "RecentPaths will be initialized as an empty vector." << std::endl;
            recentPaths.clear(); // 确保在异常情况下也清空
        } catch (const nlohmann::json::exception& e) {
            // 捕获所有 nlohmann::json 相关的其他异常（例如解析错误）
            std::cerr << "Caught other JSON exceptions: " << e.what() << std::endl;
            std::cerr << "recentPaths will be initialized as an empty vector." << std::endl;
            recentPaths.clear();
        } catch (const std::exception& e) {
            // 捕获所有标准库异常
            std::cerr << "Caught an unknown exception:" << e.what() << std::endl;
            std::cerr << "recentPaths will be initialized as an empty vector." << std::endl;
            recentPaths.clear();
        }
    }

void ConfigManager::saveConfig(const std::string &filePath) {
    Config["defaultPath"] = defaultPath;
    Config["showHidden"] = showHidden;
    Config["recentPath"]=recentPaths;
    //获取当前的defaultPath、showHidden、recentPath存储进Config.json文件中
    std::ofstream ofs;
    //用覆盖模式写入，以便于更新到最新的状态
    ofs.open(filePath,std::ios::ate);
    if (!ofs.is_open()) {
        std::cerr<<"File open failed"<<std::endl;
        return;
    }
    //简单写入
    //ofs<<Config;
    //格式化写入每行缩进两格
    ofs<<Config.dump(2);
    ofs.close();
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
        recentPaths.push_back(path);
        std::cout<<"recentPaths successfully added"<<std::endl;
    }else {
        std::cout<<"The length of the recentPath array cannot exceed 5"<<std::endl;
        return;
    }

}

void ConfigManager::setDefaultPath(const std::string &path) {
    defaultPath=path;
}

void ConfigManager::setShowHidden(const bool &val) {
    showHidden=val;
}
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
