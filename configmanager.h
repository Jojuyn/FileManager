//
// Created by kychen on 25-7-11.
//

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
#include <nlohmann/json.hpp>
#include <string>

class ConfigManager {
public:
    //从文件加载配置到内存
    void loadConfig(const std::string& filePath);
    //将内存配置写入文件
    void saveConfig(const std::string& filePath);
    //获取默认路径
    std::string getDefaultPath() const;
    //获取showHidden参数
    bool getShowHidden()const;
    //获取历史路径
    std::vector<std::string> getRecentPaths()const;
    //添加最近的访问路径
    void addRecentPath(const std::string& path);
    //清空历史记录
    void clearRecentPath();
    //修改默认路径
    void setDefaultPath(const std::string& path);
    //设置是否展示隐藏文件 默认为true
    void setShowHidden(const bool &val);

    // 拓展功能
    // 其他配置项：主题设置、视图模式、快捷键映射等
    void setTheme(const std::string &theme);
    std::string getTheme() const;

    //新增文件格式过滤器系列函数
    void setFileFilter(const std::vector<std::string> &fileFilter);
    std::vector<std::string> getFileFilter()const;
    void addfileFilter(const std::string &fileExtension);
    void clearFileFilter();


private:
    std::string defaultPath;
    std::vector<std::string> recentPaths;
    //新增文件筛选数组，用于存储所需要筛选的文件拓展名
    std::vector<std::string> fileFilterExtension;
    bool showHidden=true;
    nlohmann::json Config;
    std::string Theme;
};
#endif //CONFIGMANAGER_H
