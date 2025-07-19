#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>

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

    void on_pushButton_clicked();

private:
    Ui::Cell_Main *ui;
    QString m_strDataPath;
    QStandardItemModel *m_model;

    QTimer m_timer;
    QString m_cur;
};
#endif // CELL_MAIN_H
