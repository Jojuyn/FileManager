<<<<<<< HEAD
cmake_minimum_required(VERSION 3.19)
project(FileManager LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(FileManager
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ExceptionHandler.cpp
    ExceptionHandler.h
    FileOperations.cpp
    FileOperations.h
ConfigManager.cpp
    ConfigManager.h
    Header.h
)

target_link_libraries(FileManager
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS FileManager
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET FileManager
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# 添加 nlohmann/json 子目录
add_subdirectory(thirdparty/json) # 路径根据你实际放置的位置调整


# 链接 nlohmann/json 库提供的 target
# nlohmann_json::nlohmann_json 是 nlohmann/json 库自己定义的 CMake target
target_link_libraries(Project2 PRIVATE nlohmann_json::nlohmann_json)

