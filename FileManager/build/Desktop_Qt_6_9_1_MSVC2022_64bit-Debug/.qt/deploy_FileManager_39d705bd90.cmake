include("D:/Workspace/TuringNinth/FileManager/FileManager/build/Desktop_Qt_6_9_1_MSVC2022_64bit-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/FileManager-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE D:/Workspace/TuringNinth/FileManager/FileManager/build/Desktop_Qt_6_9_1_MSVC2022_64bit-Debug/FileManager.exe
    GENERATE_QT_CONF
)
