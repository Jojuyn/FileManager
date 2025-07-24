#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QFileDialog>
#include <QMessageBox>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , configManager(nullptr)
{
    ui->setupUi(this);

    // 初始化主题下拉菜单
    ui->themeComboBox->addItem("原神", "原神");
    ui->themeComboBox->addItem("明日方舟", "明日方舟");
    ui->themeComboBox->addItem("赛博朋克", "赛博朋克");

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setConfigManager(ConfigManager *manager)
{
    configManager = manager;
}

void SettingsDialog::loadSettings()
{
    if (!configManager) return;

    ui->defaultPathLineEdit->setText(QString::fromStdString(configManager->getDefaultPath()));
    ui->showHiddenCheckBox->setChecked(configManager->getShowHidden());

    // 加载主题
    QString currentTheme = QString::fromStdString(configManager->getTheme());
    int index = ui->themeComboBox->findData(currentTheme);
    if (index != -1) {
        ui->themeComboBox->setCurrentIndex(index);
    } else {
        ui->themeComboBox->setCurrentIndex(0); // 默认选择第一个主题
    }

    ui->extensionsListWidget->clear();
    for (const auto &ext : configManager->getFileFilter()) {
        ui->extensionsListWidget->addItem(QString::fromStdString(ext));
    }

    ui->recentPathsListWidget->clear();
    for (const auto &path : configManager->getRecentPaths()) {
        ui->recentPathsListWidget->addItem(QString::fromStdString(path));
    }
}

void SettingsDialog::on_browseDefaultPathButton_clicked()
{
    QString initialDir = ui->defaultPathLineEdit->text();
    if (initialDir.isEmpty()) {
        initialDir = QDir::homePath();
    }
    QString path = QFileDialog::getExistingDirectory(this, tr("选择默认路径"), initialDir);
    if (!path.isEmpty()) {
        ui->defaultPathLineEdit->setText(path);
    }
}

void SettingsDialog::on_addExtensionButton_clicked()
{
    QString ext = ui->newExtensionLineEdit->text().trimmed();
    if (!ext.isEmpty()) {
        ui->extensionsListWidget->addItem(ext);
        ui->newExtensionLineEdit->clear();
    }
}

void SettingsDialog::on_removeExtensionButton_clicked()
{
    QList<QListWidgetItem *> selectedItems = ui->extensionsListWidget->selectedItems();
    for (auto item : selectedItems) {
        delete ui->extensionsListWidget->takeItem(ui->extensionsListWidget->row(item));
    }
}

void SettingsDialog::on_clearRecentPathsButton_clicked()
{
    if (configManager) {
        configManager->clearRecentPath();
        configManager->saveConfig("config.json");
        ui->recentPathsListWidget->clear();
    }
}

void SettingsDialog::on_applyButton_clicked()
{
    if (!configManager) {
        QMessageBox::warning(this, tr("错误"), tr("配置管理器未初始化！"));
        return;
    }

    // 验证路径有效性
    QDir dir(ui->defaultPathLineEdit->text());
    if (!dir.exists()) {
        QMessageBox::warning(this, tr("警告"), tr("默认路径无效！"));
        return;
    }

    configManager->setDefaultPath(ui->defaultPathLineEdit->text().toStdString());
    configManager->setShowHidden(ui->showHiddenCheckBox->isChecked());
    configManager->setTheme(ui->themeComboBox->currentData().toString().toStdString());
    emit themeChanged(ui->themeComboBox->currentText()); // 发出主题变化信号

    std::vector<std::string> extensions;
    for (int i = 0; i < ui->extensionsListWidget->count(); ++i) {
        extensions.push_back(ui->extensionsListWidget->item(i)->text().toStdString());
    }
    configManager->setFileFilter(extensions);

    configManager->saveConfig("config.json");
    accept();
}

void SettingsDialog::on_cancelButton_clicked()
{
    reject();
}
