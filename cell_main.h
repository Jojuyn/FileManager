#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include "include.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Cell_Main;
}
QT_END_NAMESPACE

class Cell_Main : public QMainWindow
{
    Q_OBJECT

public:
    Cell_Main(QWidget *parent = nullptr);
    ~Cell_Main();
    void updateFile();

private slots:
    void on_btn_upload_clicked();

    void on_btn_open_clicked();

    void on_btn_del_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_trashBtn_clicked();    //新增打开回收站的槽函数
    void on_copyBtn_clicked();     //新增复制槽函数
    void on_pasteBtn_clicked();    //新增粘贴槽函数
    void on_renameBtn_clicked();

private:
    Ui::Cell_Main *ui;
    QString m_strDataPath;
    QString m_strRecyclePath;      //新增回收站路径
    QString m_copiedFilePath;      //存储复制文件路径

    QStandardItemModel *m_model;
    QTimer m_timer;
    QString m_cur;

    QString m_selectedFilePath; // 存储当前选中文件的路径
    bool moveToRecycleBin(const QFileInfo& fileInfo);         //新增移到回收站函数
    QString type_filter = "*.txt*.md";
};
#endif // CELL_MAIN_H
