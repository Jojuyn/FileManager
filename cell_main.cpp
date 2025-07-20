#include "cell_main.h"
#include "ui_cell_main.h"
#include<QDir>
#include <QUrl>
#include <QFile>
#include<QtDebug>
#include<QDateTime>
#include <QFileInfo>
#include<QFileDialog>
#include<QMessageBox>
#include<QDesktopServices>
#include "FileOperation/FileOperation.h"

Cell_Main::Cell_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cell_Main)
{
    ui->setupUi(this);
    //获取当前应用程序所在目录
    m_strDataPath = QApplication::applicationDirPath()+"/data";
    QDir d(m_strDataPath);
    if(!d.exists()){
        d.mkdir(m_strDataPath);
    }

    m_model = new QStandardItemModel;
    connect(&m_timer,&QTimer::timeout,this,&Cell_Main::updateFile);
    m_timer.start(500);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    updateFile();
}

Cell_Main::~Cell_Main()
{
    delete ui;
    delete m_model;
}

void Cell_Main::updateFile(){

    QDir d(m_strDataPath);
    QStringList lFiter;
    lFiter<<"*.txt"<<"*.md";
    QFileInfoList lFilesInfo = d.entryInfoList(lFiter,QDir::Files);
    QString strFilter = ui->lineEdit->text();
    QString strFlag;
    QList<QStandardItem*> lRow;
    QStandardItemModel *m_temModel=new QStandardItemModel;

    //输出列表
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

void Cell_Main::on_btn_upload_clicked()
{
    auto strPath = QFileDialog::getOpenFileName(nullptr,"文件上传",QDir::homePath(),"*.txt");
    if(strPath.isEmpty()){
        QMessageBox::warning(this,"警告","本次无文件上传");
    }
    auto uploadPath = m_strDataPath+"/"+strPath.section("/",-1);
    //判断我缓存目录中是否有相同文件名的文件
    if(QFile::exists(uploadPath)){
        QMessageBox::warning(nullptr,"文件已存在","请重新命名！！！");
        return;
    }
    bool ret = QFile::copy(strPath,uploadPath);
    if(!ret){
        QMessageBox::warning(nullptr,"信息","上传失败,可能是文件被占用");
        return;
    }
    // 上传成功后更新文件列表
    updateFile();
    // 显示上传成功消息
    QMessageBox::information(nullptr, "信息", "文件上传成功");

}

void Cell_Main::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    // 获取选中行的文件路径（第2列，隐藏列）
    QModelIndex pathIndex = m_model->index(index.row(), 1);
    QString filePath = m_model->data(pathIndex).toString();

    if (filePath.isEmpty())
        return;

    // 使用系统默认程序打开文件
    bool result = QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

    if (!result) {
        QMessageBox::warning(this, "错误", "无法打开文件");
    }
}




void Cell_Main::on_btn_open_clicked()
{
    QDesktopServices::openUrl(QUrl(m_strDataPath));
}

void Cell_Main::on_btn_del_clicked()
{
    auto index = ui->tableView->currentIndex();
    if(!index.isValid()){
        return;
    }

    auto itemp = m_model->index(index.row(),1);
    auto str = m_model->data(itemp).toString();
    auto ret = QFile::remove(str);
    QMessageBox::information(nullptr,"信息",ret?"文件删除成功":"文件删除失败");


}

void Cell_Main::on_trashBtn_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_strRecyclePath));
}


void Cell_Main::on_copyBtn_clicked()
{
    auto index = ui->tableView->currentIndex();
    if(!index.isValid()){
        QMessageBox::warning(this,"警告","请先选择要复制的文件");
    }

    //获取当前选中的文件路径
    auto filePathIndex = m_model->index(index.row(), 1);
    m_copiedFilePath = m_model->data(filePathIndex).toString();

    // 也可以将文件路径放入剪贴板，这样可以在其他应用中使用
    QApplication::clipboard()->setText(m_copiedFilePath);
}


void Cell_Main::on_pasteBtn_clicked()
{
    if(m_copiedFilePath.isEmpty()){
        QMessageBox::warning(this,"警告","没有可粘贴的文件");
        return;
    }

    QFileInfo fileInfo(m_copiedFilePath);
    QString baseName = fileInfo.completeBaseName(); //文件名
    QString suffix = fileInfo.suffix();             //扩展名
    QString newFilePath;
    int counter = 1;

    //初始尝试使用原文件名
    newFilePath = m_strDataPath + "/" + fileInfo.fileName();

    //检查文件是否存在，如果存在则添加序号
    while (QFile::exists(newFilePath)) {
        newFilePath = m_strDataPath + "/" + baseName +
                      "副本(" + QString::number(counter) + ")." + suffix;
        counter++;
    }
    // 执行文件复制
    if (QFile::copy(m_copiedFilePath, newFilePath)) {
        QMessageBox::information(this, "信息", "文件粘贴成功");
        updateFile(); // 刷新文件列表
    } else {
        QMessageBox::warning(this, "错误", "粘贴失败");
    }

}



void Cell_Main::on_renameBtn_clicked()
{

}

