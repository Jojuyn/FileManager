#include "cell_main.h"
#include "ui_cell_main.h"
#include<QDir>
#include<QtDebug>
#include<QDateTime>
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
        return;
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


void Cell_Main::on_pushButton_clicked()
{

}

