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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshCurrentView(); // 刷新当前路径的文件列表
    void setCurrentPath(); // 设置当前显示路径
    QString currentPath() const; // 获取当前路径

signals:
    // 转发文件操作请求(供其他模块连接用)
    void createFileRequested(const QString& path);
    void createDirRequested(const QString& path);
    void copyRequested(const QStringList& sources, const QString& dest);
    void moveRequested(const QStringList& sources, const QString& dest);
    void deleteRequested(const QStringList& paths, bool permanent);
    void searchRequested(const QString& keyword);

private slots:
    // 工具栏/菜单动作处理
    void onActionNewFile();
    void onActionNewDir();
    void onActionCopy();
    void onActionCut();
    void onActionPaste();
    void onActionDelete();
    void onActionRefresh();
    void onActionGoBack();
    void onActionGoForward();
    void onActionGoUp();
    void onActionGoHome();
    void onActionSearch();
    // 视图交互处理
    void onTreeViewClicked(const QModelIndex& index);
    void onFileViewDoubleClicked(const QModelIndex& index);
    void onPathEditReturnPressed();
    void onSearchEditReturnPressed();
    // 接收其他模块的反馈
    void onFileOpStarted(const QString& opName);
    void onFileOpCompleted(const QString& opName, bool success);
    void onFileOpProgress(qint64 done, qint64 total);

private:
    Ui::MainWindow *ui;
    // UI组件
    QToolBar* m_mainToolBar;       // 主工具栏
    QStatusBar* m_statusBar;       // 状态栏
    QLabel* m_statusLabel;         // 状态栏信息标签
    QLabel* m_progressLabel;       // 进度标签

    QSplitter* m_mainSplitter;     // 主分割器
    QTreeView* m_treeView;         // 目录树视图
    QTabWidget* m_fileViews;       // 文件视图标签页（图标/列表/详情）
    QListView* m_iconView;         // 图标视图
    QListView* m_listView;         // 列表视图
    QTableView* m_tableView;       // 详情视图

    QLineEdit* m_pathEdit;         // 路径输入框
    QLineEdit* m_searchEdit;       // 搜索输入框

    // 数据模型
    QFileSystemModel* m_fileModel; // 文件系统模型

    // 动作对象
    QAction* m_actNewFile;
    QAction* m_actNewDir;
    QAction* m_actCopy;
    QAction* m_actCut;
    QAction* m_actPaste;
    QAction* m_actDelete;
    QAction* m_actRefresh;
    QAction* m_actGoBack;
    QAction* m_actGoForward;
    QAction* m_actGoUp;
    QAction* m_actGoHome;

    // 导航历史
    QStringList m_navHistory;      // 导航历史记录
    int m_navHistoryIndex;         // 当前历史索引

    void initUI();                                 // 初始化UI
    void createActions();                          // 创建动作
    void createToolBars();                         // 创建工具栏
    void createMenus();                            // 创建菜单
    void initViews();                              // 初始化视图
    void initModels();                             // 初始化模型
    void connectSignals();                         // 连接信号槽
    QStringList getSelectedFiles() const;          // 获取选中的文件路径
    void updateNavHistory(const QString& path);    // 更新导航历史
};
#endif // MAINWINDOW_H
