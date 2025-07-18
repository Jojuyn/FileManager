cmake_minimum_required(VERSION 3.29)
project(Project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(Project2 main.cpp
        ConfigManager.cpp
        ConfigManager.h
        Header.h)

set(CMAKE_CXX_STANDARD 17) # 或者更高

# 添加 nlohmann/json 子目录
add_subdirectory(thirdparty/json) # 路径根据你实际放置的位置调整


# 链接 nlohmann/json 库提供的 target
# nlohmann_json::nlohmann_json 是 nlohmann/json 库自己定义的 CMake target
target_link_libraries(Project2 PRIVATE nlohmann_json::nlohmann_json)
