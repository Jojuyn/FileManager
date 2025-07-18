#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    createActions();                          // 创建动作
    createToolBars();                         // 创建工具栏
    createMenus();                            // 创建菜单
    initViews();                              // 初始化视图
    initModels();                             // 初始化模型
    connectSignals();                         // 连接信号槽
}
