#include "FileOperations.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStorageInfo>
#include <QProcess>
#include <QSaveFile>

// 平台特定头文件
#ifdef Q_OS_WIN
#include <windows.h>
#include <shellapi.h>
#elif defined(Q_OS_LINUX)
#include <QtDBus/QtDBus>
#elif defined(Q_OS_MACOS)
#include <CoreServices/CoreServices.h>
#endif

// ==================== 构造函数 ====================
FileOperations::FileOperations(QObject *parent)
    : QObject(parent)
{
    // 目前不需要特殊初始化
}

// ==================== 基础文件操作 ====================
bool FileOperations::createFile(const QString &filePath, const QString &content)
{
    emit operationStarted("CreateFile");//触发信号，表示开始创建文件

    QFile file(filePath);//创建一个QFile对象file，并将其与filepath指向的文件关联起来

    // 检查文件是否已存在
    if(file.exists()) {
        emit errorOccurred("File already exists");
        emit operationCompleted("CreateFile", false);
        return false;  //存在则返回0，表示创建文件失败
    }

    // 尝试打开文件进行写入
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        emit errorOccurred("Failed to open file for writing: " + file.errorString());
        emit operationCompleted("CreateFile", false);
        //文件打开或写入失败了，返回false
        return false;
    }

    // 写入内容
    QTextStream out(&file);
    out << content;
    file.close();


    emit operationCompleted("CreateFile", true);
    return true;
}

bool FileOperations::createDirectory(const QString &dirPath)
{
    emit operationStarted("CreateDirectory");
    QDir dir(dirPath);
    // 检查目录是否已存在，与上一个函数同理
    if(dir.exists()) {
        emit errorOccurred("Directory already exists");
        emit operationCompleted("CreateDirectory", false);
        return false;
    }

    // 递归创建目录
    if(!dir.mkpath(".")) {  // mkpath会自动创建所有必要的父目录
        //"."表示当前目录，如果创建目录失败，那么
        emit errorOccurred("Failed to create directory");
        emit operationCompleted("CreateDirectory", false);
        return false;
    }

    emit operationCompleted("CreateDirectory", true);
    return true;
}

bool FileOperations::deleteFile(const QString &filePath, bool permanent)
{
    emit operationStarted(permanent ? "DeleteFile" : "MoveToTrash");

    // 检查文件是否存在
    if(!QFile::exists(filePath)) {
        emit errorOccurred("File does not exist");
        emit operationCompleted(permanent ? "DeleteFile" : "MoveToTrash", false);
        return false;
    }

    bool result = false;

    if(permanent) {
        // 永久删除文件
        result = QFile::remove(filePath);
        if(!result) {
            emit errorOccurred("Failed to delete file");
        }
    } else {
        // 移动到回收站
        result = moveToRecycleBin(filePath);
    }

    emit operationCompleted(permanent ? "DeleteFile" : "MoveToTrash", result);
    return result;
}
bool FileOperations::deleteDirectory(const QString &dirPath, bool permanent)
{
    emit operationStarted(permanent ? "DeleteDirectory" : "MoveToTrash");

    QDir dir(dirPath);

    // 检查目录是否存在
    if(!dir.exists()) {
        emit errorOccurred("Directory does not exist");
        emit operationCompleted(permanent ? "DeleteDirectory" : "MoveToTrash", false);
        return false;
    }

    bool result = false;
    if(permanent) {
        // 永久删除目录及其内容
        result = dir.removeRecursively();
        if(!result) {
            emit errorOccurred("Failed to delete directory");
        }
    } else {
        // 移动到回收站
        result = moveToRecycleBin(dirPath);
    }

    emit operationCompleted(permanent ? "DeleteDirectory" : "MoveToTrash", result);
    return result;
}

bool FileOperations::rename(const QString &oldPath, const QString &newName)
{
    emit operationStarted("Rename");

    QFileInfo oldInfo(oldPath);
    QString newPath = oldInfo.absoluteDir().absoluteFilePath(newName);

    // 检查源文件是否存在
    if(!oldInfo.exists()) {
        emit errorOccurred("Source file does not exist");
        emit operationCompleted("Rename", false);
        return false;
    }

    // 检查目标文件是否已存在
    if(QFile::exists(newPath)) {
        emit errorOccurred("Target file already exists");
        emit operationCompleted("Rename", false);
        return false;
    }

    // 执行重命名
    bool result = QFile::rename(oldPath, newPath);
    if(!result) {
        emit errorOccurred("Failed to rename file");
    }

    emit operationCompleted("Rename", result);
    return result;
}


// ==================== 文件操作 ====================
bool FileOperations::copy(const QString &source, const QString &destination)
{
    emit operationStarted("Copy");

    // 检查源文件是否存在
    if(!QFile::exists(source)) {
        emit errorOccurred("Source file does not exist");
        emit operationCompleted("Copy", false);
        return false;
    }

    // 检查目标文件是否已存在
    if(QFile::exists(destination)) {
        emit errorOccurred("Destination file already exists");
        emit operationCompleted("Copy", false);
        return false;
    }

    // 检查目标路径是否有足够空间
    QStorageInfo storage(QFileInfo(destination).absoluteDir());
    if(storage.bytesAvailable() < QFileInfo(source).size()) {
        emit errorOccurred("Not enough disk space");
        emit operationCompleted("Copy", false);
        return false;
    }

    // 使用QSaveFile进行安全的文件复制
    QFile srcFile(source);
    QSaveFile destFile(destination);

    if(!srcFile.open(QIODevice::ReadOnly)) {
        emit errorOccurred("Failed to open source file: " + srcFile.errorString());
        emit operationCompleted("Copy", false);
        return false;
    }

    if(!destFile.open(QIODevice::WriteOnly)) {
        emit errorOccurred("Failed to open destination file: " + destFile.errorString());
        emit operationCompleted("Copy", false);
        return false;
    }

    // 分块复制文件
    const qint64 bufferSize = 1024 * 1024; // 1MB缓冲区
    char buffer[bufferSize];
    qint64 totalBytes = srcFile.size();
    qint64 bytesCopied = 0;

    while(!srcFile.atEnd()) {
        qint64 read = srcFile.read(buffer, bufferSize);
        if(read == -1) {
            emit errorOccurred("Error reading source file");
            emit operationCompleted("Copy", false);
            return false;
        }

        if(destFile.write(buffer, read) != read) {
            emit errorOccurred("Error writing to destination file");
            emit operationCompleted("Copy", false);
            return false;
        }

        bytesCopied += read;
        // 可以在这里发射进度信号，如果需要的话
        // emit progressChanged(bytesCopied * 100 / totalBytes);
    }

    // 确保所有数据都写入磁盘
    if(!destFile.commit()) {
        emit errorOccurred("Failed to commit changes to destination file");
        emit operationCompleted("Copy", false);
        return false;
    }

    emit operationCompleted("Copy", true);
    return true;
}

bool FileOperations::move(const QString &source, const QString &destination)
{
    emit operationStarted("Move");

    // 先尝试直接重命名（同设备移动）
    if(QFile::rename(source, destination)) {
        emit operationCompleted("Move", true);
        return true;
    }

    // 跨设备移动需要复制+删除
    if(copy(source, destination)) {
        bool deleteResult = deleteFile(source, true);
        emit operationCompleted("Move", deleteResult);
        return deleteResult;
    }

    emit operationCompleted("Move", false);
    return false;
}

// ==================== 属性管理 ====================
QVariantMap FileOperations::getFileProperties(const QString &path)
{
    QVariantMap props;
    QFileInfo info(path);

    if(!info.exists()) {
        emit errorOccurred("File not found");
        return props;
    }

    // TODO: 填充属性字段
    props["size"] = info.size();
    props["lastModified"] = info.lastModified();

    return props;
}

bool FileOperations::setFileModifiedTime(const QString &path, const QDateTime &time)
{
    // TODO: 实现修改时间
    return false;
}

// ==================== 平台私有方法 ====================
#ifdef Q_OS_WIN
bool windowsMoveToRecycleBin(const QString &path)
{
    // Windows API 实现
    SHFILEOPSTRUCTW op;
    ZeroMemory(&op, sizeof(op));

    // TODO: 填充结构体参数
    // op.pFrom = 转换路径为LPCWSTR
    // op.wFunc = FO_DELETE;
    // op.fFlags = FOF_ALLOWUNDO;

    int result = SHFileOperationW(&op);
    return result == 0;
}
#elif defined(Q_OS_LINUX)
bool FileOperations::linuxMoveToTrash(const QString &path)
{
    // DBus 或 gio 命令实现
    return QProcess::execute("gio", {"trash", path}) == 0;
}
#endif

// ==================== 辅助方法 ====================
bool ensureDirectoryExists(const QString &path)
{
    // TODO: 确保目录存在
    return true;
}

// ==================== 回收站操作 ====================
bool FileOperations::moveToRecycleBin(const QString &path)
{
    emit operationStarted("MoveToRecycleBin");

    bool result = false;

#ifdef Q_OS_WIN
    // Windows 实现
    result = windowsMoveToRecycleBin(path);
#elif defined(Q_OS_LINUX)
    // Linux 实现
    result = linuxMoveToTrash(path);
#elif defined(Q_OS_MACOS)
    // macOS 实现
    result = macMoveToTrash(path);
#else
    // 其他平台回退
    result = QFile::remove(path);
#endif

    emit operationCompleted("MoveToRecycleBin", result);
    return result;
}

bool FileOperations::restoreFromRecycleBin(const QString &path)
{
    // TODO: 各平台恢复实现
    return false;
}


