#include "cell_main.h"
#include "ui_cell_main.h"
#include <QDir>
#include <QUrl>
#include <QFile>
#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QPainter>

Cell_Main::Cell_Main(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Cell_Main)
    , settingsDialog(new SettingsDialog(this))
    , m_model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    // 初始化数据目录
    m_strDataPath = QApplication::applicationDirPath() + "/data";
    QDir d(m_strDataPath);
    if (!d.exists()) {
        d.mkdir(m_strDataPath);
    }

    // 加载配置
    configManager.loadConfig("config.json");

    // 初始化表格
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(m_model);

    // 初始化定时器
    connect(&m_timer, &QTimer::timeout, this, &Cell_Main::updateFile);
    m_timer.start(500);

    // 连接设置按钮
    connect(ui->settingBtn, &QPushButton::clicked, this, &Cell_Main::on_settingBtn_clicked);
    // 连接主题变化信号
    connect(settingsDialog, &SettingsDialog::themeChanged, this, &Cell_Main::applyTheme);

    // 应用初始主题
    applyTheme(QString::fromStdString(configManager.getTheme()));

    updateFile();
}

Cell_Main::~Cell_Main()
{
    configManager.saveConfig("config.json");
    delete settingsDialog;
    delete m_model;
    delete ui;
}

void Cell_Main::updateFile()
{
    QDir d(m_strDataPath);
    QStringList lFilter;
    lFilter << "*.txt" << "*.md";
    QFileInfoList lFilesInfo = d.entryInfoList(lFilter, QDir::Files);
    QString strFilter = ui->lineEdit->text();
    QString strFlag;
    QList<QStandardItem*> lRow;
    QStandardItemModel *m_temModel = new QStandardItemModel;

    for (int i = 0; i < lFilesInfo.size(); i++) {
        lRow.clear();
        QFileInfo &info = lFilesInfo[i];
        if (!info.completeBaseName().contains(strFilter)) {
            continue;
        }
        QStandardItem *p1 = new QStandardItem(info.completeSuffix());
        strFlag = strFlag + info.absoluteFilePath();
        QStandardItem *p2 = new QStandardItem(info.absoluteFilePath());
        QStandardItem *p3 = new QStandardItem(info.baseName());
        QStandardItem *p4 = new QStandardItem(info.birthTime().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p5 = new QStandardItem(info.lastModified().toString("yyyy/MM/dd hh:mm:ss"));
        QStandardItem *p6 = new QStandardItem(QString::number(info.size()) + "B");
        lRow << p3 << p2 << p4 << p5 << p1 << p6;
        m_temModel->appendRow(lRow);
    }

    if (strFlag == m_cur) {
        delete m_temModel;
        return;
    }

    delete m_model;
    m_model = nullptr;
    m_model = m_temModel;
    m_cur = strFlag;

    QStringList lHeaders{"文件名", "绝对路径", "创建日期", "最后一次修改", "文件类型", "文件大小"};
    m_model->setHorizontalHeaderLabels(lHeaders);
    ui->tableView->setModel(m_model);
}

void Cell_Main::on_btn_upload_clicked()
{
    auto strPath = QFileDialog::getOpenFileName(nullptr, "文件上传", QDir::homePath(), "*.txt");
    if (strPath.isEmpty()) {
        QMessageBox::warning(this, "警告", "本次无文件上传");
        return;
    }
    auto uploadPath = m_strDataPath + "/" + strPath.section("/", -1);
    if (QFile::exists(uploadPath)) {
        QMessageBox::warning(nullptr, "文件已存在", "请重新命名！！！");
        return;
    }
    bool ret = QFile::copy(strPath, uploadPath);
    if (!ret) {
        QMessageBox::warning(nullptr, "信息", "上传失败,可能是文件被占用");
        return;
    }
    updateFile();
    QMessageBox::information(nullptr, "信息", "文件上传成功");
}

void Cell_Main::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
        return;

    QModelIndex pathIndex = m_model->index(index.row(), 1);
    QString filePath = m_model->data(pathIndex).toString();

    if (filePath.isEmpty())
        return;

    bool result = QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

    if (!result) {
        QMessageBox::warning(this, "错误", "无法打开文件");
    }
}

void Cell_Main::on_btn_open_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("打开文件夹"),
                                                     QString::fromStdString(configManager.getDefaultPath()));
    if (!path.isEmpty()) {
        configManager.addRecentPath(path.toStdString());
        configManager.saveConfig("config.json");
        m_strDataPath = path;
        updateFile();
    }
}

void Cell_Main::on_btn_del_clicked()
{
    auto index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        return;
    }

    auto itemp = m_model->index(index.row(), 1);
    auto str = m_model->data(itemp).toString();
    auto ret = QFile::remove(str);
    QMessageBox::information(nullptr, "信息", ret ? "文件删除成功" : "文件删除失败");
}

void Cell_Main::on_settingBtn_clicked()
{
    settingsDialog->setConfigManager(&configManager);
    settingsDialog->loadSettings();
    settingsDialog->exec();
}

void Cell_Main::on_trashBtn_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_strRecyclePath));
}

void Cell_Main::on_copyBtn_clicked()
{
    auto index = ui->tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "警告", "请先选择要复制的文件");
        return;
    }

    auto filePathIndex = m_model->index(index.row(), 1);
    m_copiedFilePath = m_model->data(filePathIndex).toString();
    QApplication::clipboard()->setText(m_copiedFilePath);
}

void Cell_Main::on_pasteBtn_clicked()
{
    if (m_copiedFilePath.isEmpty()) {
        QMessageBox::warning(this, "警告", "没有可粘贴的文件");
        return;
    }

    QFileInfo fileInfo(m_copiedFilePath);
    QString baseName = fileInfo.completeBaseName();
    QString suffix = fileInfo.suffix();
    QString newFilePath;
    int counter = 1;

    newFilePath = m_strDataPath + "/" + fileInfo.fileName();
    while (QFile::exists(newFilePath)) {
        newFilePath = m_strDataPath + "/" + baseName +
                      "副本(" + QString::number(counter) + ")." + suffix;
        counter++;
    }
    if (QFile::copy(m_copiedFilePath, newFilePath)) {
        QMessageBox::information(this, "信息", "文件粘贴成功");
        updateFile();
    } else {
        QMessageBox::warning(this, "错误", "粘贴失败");
    }
}

void Cell_Main::on_renameBtn_clicked()
{
    // 实现重命名逻辑
}

void Cell_Main::setBackgroundImage(const QString &imagePath)
{
    backgroundImage = QPixmap(imagePath);
    if (backgroundImage.isNull()) {
        qWarning() << "Failed to load background image:" << imagePath;
    } else {
        qDebug() << "Background image loaded successfully:" << imagePath;
    }
    update();
}

void Cell_Main::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    if (!backgroundImage.isNull()) {
        QPainter painter(this);
        QSize scaledSize = backgroundImage.size();
        scaledSize.scale(size(), Qt::KeepAspectRatioByExpanding);
        QRect targetRect(QPoint(0, 0), scaledSize);
        targetRect.moveCenter(rect().center());
        painter.drawPixmap(targetRect, backgroundImage);
    }
}

void Cell_Main::applyTheme(const QString &theme)
{
    qDebug() << "Applying theme:" << theme;
    QString styleSheet = getThemeStyle(theme);
    QString backgroundPath = getThemeBackground(theme);
    setStyleSheet(styleSheet);
    if (!backgroundPath.isEmpty()) {
        setBackgroundImage(backgroundPath);
        ui->tableView->setStyleSheet("QTableView { background-color: rgba(255, 255, 255, 50); }");
        qDebug() << "TableView style set to semi-transparent";
    } else {
        setBackgroundImage("");
        ui->tableView->setStyleSheet("");
        qDebug() << "TableView style cleared";
    }
}

QString Cell_Main::getThemeStyle(const QString &theme) const
{
    if (theme == "原神") {
        return GenshinStyle;
    } else if (theme == "明日方舟") {
        return ArknightsStyle;
    } else if (theme == "赛博朋克") {
        return CyberpunkStyle;
    }
    return "";
}

QString Cell_Main::getThemeBackground(const QString &theme) const
{
    if (theme == "原神") {
        return ":/wallpapers/Furina-3.png";
    } else if (theme == "明日方舟") {
        return ":/wallpapers/Amiya.png";
    } else if (theme == "赛博朋克") {
        return ":/wallpapers/Cyberpunk.jpg";
    }
    return "";
}
