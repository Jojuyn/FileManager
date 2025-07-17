#include "filemanager.h"
#include "ui_filemanager.h"
// #include "FileOperations.h"
// #include "SearchManager.h"
// #include "ConfigManager.h"
// #include "ExceptionHandler.h"
#include <QDir>
#include <QFileInfo>
#include <QMessageBox>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>

FileManager::FileManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FileManager)
{
    ui->setupUi(this);
}

FileManager::~FileManager()
{
    delete ui;
}
