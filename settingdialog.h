#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "configmanager.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    void setConfigManager(ConfigManager *manager);
    void loadSettings();

private slots:
    void on_browseDefaultPathButton_clicked();
    void on_addExtensionButton_clicked();
    void on_removeExtensionButton_clicked();
    void on_clearRecentPathsButton_clicked();
    void on_applyButton_clicked();
    void on_cancelButton_clicked();
signals:
    void themeChanged(const QString &theme); // 新增：主题变化信号

private:
    Ui::SettingsDialog *ui;
    ConfigManager *configManager;
};

#endif // SETTINGDIALOG_H
