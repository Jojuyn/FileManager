#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTimer>
#include <QDir>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QClipboard>
#include "settingdialog.h"
#include "configmanager.h"

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

public slots:
    void setBackgroundImage(const QString &imagePath);
    void paintEvent(QPaintEvent *event);
    void applyTheme(const QString &theme);

private slots:
    void on_btn_upload_clicked();
    void on_btn_open_clicked();
    void on_btn_del_clicked();
    void on_settingBtn_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_trashBtn_clicked();
    void on_copyBtn_clicked();
    void on_pasteBtn_clicked();
    void on_renameBtn_clicked();

signals:
    void themeChanged(const QString &theme);

private:
    Ui::Cell_Main *ui;
    QString m_strDataPath;
    QString m_strRecyclePath;
    QString m_copiedFilePath;
    QStandardItemModel *m_model;
    QTimer m_timer;
    QString m_cur;
    QString m_selectedFilePath;
    QString type_filter = "*.txt *.md";
    QPixmap backgroundImage;
    SettingsDialog *settingsDialog;
    ConfigManager configManager;

    // 简化后的主题样式
    QString GenshinStyle = R"(
        QPushButton {
            background-color: #000000;
            border-radius: 7px;
            color: #87CEFA;
            border: 2px solid #1E90FF;
            padding: 4px 8px;
            font-weight: bold;
            font-size: 10pt;
        }
        QPushButton:hover {
            background-color: #0A0A0A;
            color: #A7E9FF;
        }
        QPushButton:pressed {
            background-color: #111111;
            color: #6CB4EE;
        }
        QPushButton:disabled {
            background-color: #222222;
            color: #888888;
            border: 2px solid #555555;
        }
    )";
    QString ArknightsStyle = R"(
        QPushButton {
            background-color: #0A1428;
            border-radius: 7px;
            color: #D4AF37;
            border: 1.5px solid #B08D57;
            padding: 4px 8px;
            font-weight: bold;
            font-size: 10pt;
        }
        QPushButton:hover {
            background-color: #0F1E35;
            color: #FFD700;
        }
        QPushButton:pressed {
            background-color: #080F1C;
            color: #B39724;
        }
        QPushButton:disabled {
            background-color: #1A2435;
            color: #5D7080;
            border: 1px solid #3A4D66;
        }
    )";
    QString CyberpunkStyle = R"(
        QPushButton {
            background-color: #0A0A0A;
            border-radius: 7px;
            color: #FFE81F;
            border: 2px solid #FF9A00;
            padding: 4px 8px;
            font-weight: bold;
            font-size: 10pt;
        }
        QPushButton:hover {
            background-color: #111111;
            color: #FFFF7A;
        }
        QPushButton:pressed {
            background-color: #0D0D0D;
            color: #FFD700;
        }
        QPushButton:disabled {
            background-color: #1A1A1A;
            color: #555555;
            border: 1px solid #FF9A00;
        }
    )";

    QString getThemeStyle(const QString &theme) const;
    QString getThemeBackground(const QString &theme) const;
};

#endif // CELL_MAIN_H
