#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include <QTreeView>
#include <QListView>
#include <QTableView>
#include <QSplitter>
#include <QToolBar>
#include <QStatusBar>
#include <QLineEdit>
#include <QAction>
#include <QTabWidget>
#include <QLabel>
#include <QFileSystemModel>
#include <QPointer>


// 前置声明其他模块
class FileOperations;   // 文件操作请求处理模块
class SearchManager;    // 输入搜索处理模块
class ConfigManager;    // 配置模块
class ExceptionHandler; // 异常处理模块

namespace Ui {
class FileManager;
}

class FileManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileManager(QWidget *parent = nullptr);
    ~FileManager();

    bool initialze(); // 初始化


private:
    Ui::FileManager *ui;
};

#endif // FILEMANAGER_H
