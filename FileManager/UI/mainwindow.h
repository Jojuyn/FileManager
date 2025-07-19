#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
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


// 前置声明业务类（不包含实现细节）
class FileOperator;
class FileSearcher;
class ConfigManager;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // === UI刷新接口 ===
    void refreshCurrentView();

    // === 路径管理接口 ===
    void setCurrentPath(const QString &path);
    QString currentPath() const;

    void loadConfig();

signals:
    // === 文件操作信号（供业务类连接） ===
    void createFileRequested(const QString &path);
    void createDirRequested(const QString &path);
    void copyRequested(const QStringList &sources, const QString &dest);
    void moveRequested(const QStringList &sources, const QString &dest);
    void deleteRequested(const QStringList &paths, bool permanent);
    void searchRequested(const QString &keyword);

public slots:
    // === 业务反馈槽函数 ===
    void onFileOpStarted(const QString &opName);
    void onFileOpCompleted(const QString &opName, bool success);
    void onFileOpProgress(qint64 done, qint64 total);

private slots:
    // === UI事件处理槽函数 ===
    // 文件操作
    void onActionNewFile();
    void onActionNewDir();
    void onActionCopy();
    void onActionCut();
    void onActionPaste();
    void onActionDelete();

    // 导航操作
    void onActionRefresh();
    void onActionGoBack();
    void onActionGoForward();
    void onActionGoUp();
    void onActionGoHome();
    void onActionSearch();

    // 视图交互
    void onTreeViewClicked(const QModelIndex &index);
    void onFileViewDoubleClicked(const QModelIndex &index);
    void onPathEditReturnPressed();
    void onSearchEditReturnPressed();

private:
    Ui::MainWindow *ui;

    // === 业务对象指针 ===
    FileOperator *m_fileOperator;
    FileSearcher *m_fileSearcher;
    ConfigManager *m_configManager;

    // === UI组件指针 ===
    QToolBar *m_mainToolBar;
    QStatusBar *m_statusBar;
    QLabel *m_statusLabel;
    QLabel *m_progressLabel;
    QSplitter *m_mainSplitter;
    QTreeView *m_treeView;
    QTabWidget *m_fileViews;
    QListView *m_iconView;
    QListView *m_listView;
    QTableView *m_tableView;
    QLineEdit *m_pathEdit;
    QLineEdit *m_searchEdit;

    // === 数据模型 ===
    QFileSystemModel *m_fileModel;

    // === 初始化方法 ===
    void initUI();                  // UI组件初始化
    void createActions();           // 创建动作对象
    void initModels();              // 初始化数据模型
    void initBusinessObjects();     // 初始化业务对象
    void connectSignals();          // 信号槽连接

    // === 辅助方法 ===
    QStringList getSelectedFiles() const; // 获取选中文件
};
#endif // MAINWINDOW_H
