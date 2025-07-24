#include "themechoose.h"
#include "ui_themechoose.h"

ThemeChoose::ThemeChoose(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ThemeChoose)
{
    ui->setupUi(this);
}

ThemeChoose::~ThemeChoose()
{
    delete ui;
}
