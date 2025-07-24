#ifndef RECYCLEBINWINDOW_H
#define RECYCLEBINWINDOW_H
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>
#include<QDir>
#include<QtDebug>
#include<QDateTime>
#include<QFileDialog>
#include<QMessageBox>
#include<QDesktopServices>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>
#include <QClipboard>
#include <QInputDialog>


namespace Ui {
class RecycleBinWindow;
}

class RecycleBinWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RecycleBinWindow(QWidget *parent = nullptr);
    ~RecycleBinWindow();
    void updateFile();


private slots:
    void on_Restroe_clicked();

    void on_Delete_clicked();

private:
    Ui::RecycleBinWindow *ui;
    QString m_strRecyclePath;
    QStandardItemModel *m_model;
    QTimer m_timer;
    QString m_cur;
    bool moveToData(const QFileInfo& fileInfo);
};

#endif // RECYCLEBINWINDOW_H
