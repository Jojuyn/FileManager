#include "recyclebinwindow.h"
#include "ui_recyclebinwindow.h"

RecycleBinWindow::RecycleBinWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RecycleBinWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("回收站");
    //获取当前应用程序所在目录
    m_strRecyclePath = QApplication::applicationDirPath()+"/data";
    m_strRecyclePath = QApplication::applicationDirPath()+"/recycle";

    QDir d(m_strRecyclePath);
    if(!d.exists()){
        d.mkdir(m_strRecyclePath);
    }

    m_model = new QStandardItemModel;
    connect(&m_timer,&QTimer::timeout,this,&RecycleBinWindow::updateFile);
    m_timer.start(500);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    updateFile();
}

void RecycleBinWindow::updateFile(){

    QDir d(m_strRecyclePath);
    QStringList lFiter;
    QFileInfoList lFilesInfo = d.entryInfoList(lFiter,QDir::Files);
    QString strFilter = ui->lineEdit->text();
    QString strFlag;
    QList<QStandardItem*> lRow;
    QStandardItemModel *m_temModel=new QStandardItemModel;
    for(int i=0;i<lFilesInfo.size();i++){
        lRow.clear();
        QFileInfo &info = lFilesInfo[i];
        if(!info.completeBaseName().contains(strFilter)){
            continue;
        }
        //序号
        QStandardItem *p1 = new QStandardItem(info.completeSuffix());
        strFlag = strFlag+info.absoluteFilePath();
        QStandardItem *p2 = new QStandardItem(info.absoluteFilePath());
        QStandardItem *p3 = new QStandardItem(info.baseName());
        QStandardItem *p4 = new QStandardItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p5 = new QStandardItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p6 = new QStandardItem(QString::number(info.size())+"B");
        lRow<<p3<<p2<<p4<<p5<<p1<<p6;
        m_temModel->appendRow(lRow);
    }
    if(strFlag == m_cur){
        delete m_temModel;
        return;
    }

    delete m_model;
    m_model = nullptr;
    m_model = m_temModel;
    m_cur = strFlag;



    QStringList lHeaders{"文件名","绝对路径","创建日期","最后一次修改","文件类型","文件大小"};
    m_model->setHorizontalHeaderLabels(lHeaders);
    ui->tableView->setModel(m_model);
}

bool RecycleBinWindow::moveToData(const QFileInfo& fileInfo){
    // 获取data目录路径（假设与回收站同级）
    QString dataPath = QApplication::applicationDirPath() + "/data";
    QDir dataDir(dataPath);

    // 如果data目录不存在则创建
    if(!dataDir.exists()) {
        dataDir.mkpath(dataPath);
    }

    // 构建目标路径
    QString destPath = dataPath + "/" + fileInfo.fileName();

    // 检查目标文件是否已存在
    if(QFile::exists(destPath)) {
        QMessageBox::warning(this, "警告", "目标文件已存在，恢复失败");
        return false;
    }

    // 执行文件移动
    QFile file(fileInfo.absoluteFilePath());
    bool success = file.rename(destPath);

    if(!success) {
        // 如果移动失败，尝试复制后删除原文件
        if(QFile::copy(fileInfo.absoluteFilePath(), destPath)) {
            success = file.remove();
        }
    }
    return success;
}


void RecycleBinWindow::on_Restroe_clicked()
{
    auto index = ui->tableView->currentIndex();
    if(!index.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要恢复的文件");
        return;
    }

    // 获取选中行的文件路径（第2列）
    QModelIndex pathIndex = m_model->index(index.row(), 1);
    QString filePath = m_model->data(pathIndex).toString();

    if(filePath.isEmpty()) {
        QMessageBox::warning(this, "错误", "无效的文件路径");
        return;
    }

    QFileInfo fileInfo(filePath);
    if(!fileInfo.exists()) {
        QMessageBox::warning(this, "错误", "文件不存在");
        return;
    }

    // 执行恢复操作
    bool ret = moveToData(fileInfo);
    if(ret) {
        QMessageBox::information(this, "信息", "文件已恢复");
        updateFile(); // 刷新回收站列表
    } else {
        QMessageBox::warning(this, "错误", "文件恢复失败");
    }

}


void RecycleBinWindow::on_Delete_clicked()
{
    auto index = ui->tableView->currentIndex();
    if(!index.isValid()){
        QMessageBox::warning(this, "警告", "请选择要删除的文件");
        return;
    }

    auto itemp = m_model->index(index.row(),1);
    auto str = m_model->data(itemp).toString();
    auto ret = QFile::remove(str);
    QMessageBox::information(nullptr,"信息",ret?"文件删除成功":"文件删除失败");
}

RecycleBinWindow::~RecycleBinWindow()
{
    delete ui;
}
