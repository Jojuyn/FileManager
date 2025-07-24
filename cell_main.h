#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include <QMainWindow>
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
#include "recyclebinwindow.h"
#include "ui_recyclebinwindow.h"
#include "configmanager.h"
#include "settingdialog.h"

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
    RecycleBinWindow *recyclebin = NULL;
    ~Cell_Main();
    void updateFile();

public slots:
    void setupConnections();
    //void refreshList();
    void setBackgroundImage(const QString &imagePath);
    void paintEvent(QPaintEvent *event);
    void applyTheme(const QString &theme);

private slots:
    void on_btn_upload_clicked();
    void on_btn_open_clicked();
    void on_btn_del_clicked();
    void on_settingBtn_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
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
    bool moveToRecycleBin(const QFileInfo& fileInfo);
    QPushButton *refreshBtn;
    QString GenshinStyle =
        // 基础样式
        "QPushButton {"
        "    background-color: black;"                // 黑色背景
        "    border-radius: 7px;"                    // 圆形边角
        "    color: qlineargradient("                 // 渐变字体
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #87CEFA, stop:1 #1E90FF);"    // 浅蓝到蓝
        "    border: 2px solid transparent;"              // 蓝色边框
        "    padding: 4px 8px;"                      // 内边距
        "    font-weight: bold;"
        "    font-size: 10pt;"
        "}"

        // 悬停效果 - 鼠标悬停时变化
        "QPushButton:hover {"
        "    background-color: #0A0A0A;"              // 稍亮的黑色
        "    border: 2px solid qlineargradient("  // 渐变边框
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #87CEFA, stop:1 #1E90FF);"
        "    color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #A7E9FF, stop:1 #4AC0FF);"
        "    color: qlineargradient("                 // 更亮的渐变字体
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #A7E9FF, stop:1 #4AC0FF);"   // 亮浅蓝到亮蓝
        "}"

        // 按下效果 - 按钮被点击时
        "QPushButton:pressed {"
        "    background-color: #111111;"              // 深灰色背景
        "    border: 2px solid qlineargradient("  // 深色渐变边框
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #6CB4EE, stop:1 #0066AA);"
        "    color: qlineargradient("                 // 深色渐变字体
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #6CB4EE, stop:1 #0066AA);"   // 深蓝渐变
        // 添加按下凹陷效果
        "    padding-top: 5px;"                       // 模拟按下效果
        "    padding-bottom: 3px;"                    // 模拟按下效果
        "}"

        // 禁用状态 - 按钮不可用时
        "QPushButton:disabled {"
        "    background-color: #222222;"              // 深灰色背景
        "    border: 2px solid #555555;"              // 灰色边框
        "    color: #888888;"                         // 灰色文字
        "}";
    QString ArknightsStyle =
        "QPushButton {"
        "    background-color: #0A1428;"                          // 深邃海军蓝背景
        "    border-radius: 7px;"
        "    color: qlineargradient("                             // 增强对比度的古铜渐变
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #D4AF37, stop:0.5 #C9A269, stop:1 #B08D57);"
        "    border: 1.5px solid transparent;"                    // 更粗的透明边框
        "    padding: 4px 8px;"
        "    font-weight: bold;"
        "    font-size: 10pt;"
        "}"
        "QPushButton:hover {"
        "    background-color: #0F1E35;"                          // 悬停时稍亮的背景
        "    border: 1.5px solid qconicalgradient("                // 增强的锥形渐变边框
        "        cx:0.5, cy:0.5, angle:0,"
        "        stop:0 #4A6585, stop:0.3 #7A9BBA, stop:0.6 #B08D57, stop:1 #D4AF37);"
        "    color: qlineargradient("                             // 高亮文字渐变
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #FFD700, stop:0.5 #E6C25C, stop:1 #D4AF37);"
        "}"
        "QPushButton:pressed {"
        "    background-color: #080F1C;"                          // 按下时深色背景
        "    border: 1.5px solid qlineargradient("                // 按下渐变边框
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #9E7C4A, stop:1 #D4AF37);"
        "    color: #B39724;"                                     // 高亮金色文字
        "    padding-top: 5px;"
        "    padding-bottom: 3px;"
        "}"
        "QPushButton:disabled {"
        "    background-color: #1A2435;"                         // 禁用状态背景
        "    color: #5D7080;"                                    // 灰蓝色文字
        "    border: 1px dashed qlineargradient("                // 渐变虚线边框
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #3A4D66, stop:1 #5D7080);"
        "}";

    QString CyberpunkStyle =      // 基础样式 - 赛博朋克黄黑主题
        "QPushButton {"
        "    background-color: #0A0A0A;"              // 深灰色背景（接近黑）
        "    border-radius: 7px;"                     // 圆形边角
        "    color: qlineargradient("                 // 黄-橙渐变字体
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #FFE81F, stop:1 #FF9A00);"    // 霓虹黄到橙色
        "    border: 2px solid transparent;"          // 透明边框（初始无边框）
        "    padding: 4px 8px;"                       // 内边距
        "    font-weight: bold;"
        "    font-size: 10pt;"
        "}"

        // 悬停效果 - 赛博朋克霓虹光效
        "QPushButton:hover {"
        "    background-color: #111111;"              // 稍亮的背景
        "    border: 2px solid qlineargradient("      // 渐变边框
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #FFE81F, stop:1 #FF9A00);"    // 黄-橙渐变
        "    color: qlineargradient("                 // 更亮的渐变字体
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #FFFF7A, stop:1 #FFC46B);"   // 亮黄到亮橙
        "}"

        // 按下效果 - 赛博朋克能量释放
        "QPushButton:pressed {"
        "    background-color: #0D0D0D;"              // 深色背景
        "    border: 2px solid #FF9A00;"              // 橙色边框（单色）
        "    color: qlineargradient("                 // 高对比渐变
        "        spread:pad, x1:0, y1:0, x2:1, y2:0,"
        "        stop:0 #FFD700, stop:1 #FF6B00);"   // 金色到深橙

        // 模拟按下效果
        "    padding-top: 5px;"
        "    padding-bottom: 3px;"
        "}"

        // 禁用状态 - 赛博朋克故障效果
        "QPushButton:disabled {"
        "    background-color: #1A1A1A;"              // 深灰背景
        "    color: #555555;"                         // 灰黄色
        "    border: 1px dashed #FF9A00;"             // 虚线边框
        "}";


    QString getThemeStyle(const QString &theme) const;
    QString getThemeBackground(const QString &theme) const;
};
#endif // CELL_MAIN_H
