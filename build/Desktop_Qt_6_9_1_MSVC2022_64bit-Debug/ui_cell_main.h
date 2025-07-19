/********************************************************************************
** Form generated from reading UI file 'cell_main.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELL_MAIN_H
#define UI_CELL_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cell_Main
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *lib_search;
    QLineEdit *lineEdit;
    QPushButton *btn_upload;
    QPushButton *btn_del;
    QPushButton *btn_open;
    QTableView *tableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Cell_Main)
    {
        if (Cell_Main->objectName().isEmpty())
            Cell_Main->setObjectName("Cell_Main");
        Cell_Main->resize(609, 391);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Cell_Main->setWindowIcon(icon);
        centralwidget = new QWidget(Cell_Main);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("QLabel{font:12px \"\351\273\221\344\275\223\";}"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        lib_search = new QLabel(frame);
        lib_search->setObjectName("lib_search");

        gridLayout->addWidget(lib_search, 0, 0, 1, 1);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        btn_upload = new QPushButton(frame);
        btn_upload->setObjectName("btn_upload");

        gridLayout->addWidget(btn_upload, 0, 2, 1, 1);

        btn_del = new QPushButton(frame);
        btn_del->setObjectName("btn_del");

        gridLayout->addWidget(btn_del, 0, 3, 1, 1);

        btn_open = new QPushButton(frame);
        btn_open->setObjectName("btn_open");

        gridLayout->addWidget(btn_open, 0, 4, 1, 1);

        tableView = new QTableView(frame);
        tableView->setObjectName("tableView");

        gridLayout->addWidget(tableView, 1, 0, 1, 5);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        Cell_Main->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Cell_Main);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 609, 18));
        Cell_Main->setMenuBar(menubar);
        statusbar = new QStatusBar(Cell_Main);
        statusbar->setObjectName("statusbar");
        Cell_Main->setStatusBar(statusbar);

        retranslateUi(Cell_Main);

        QMetaObject::connectSlotsByName(Cell_Main);
    } // setupUi

    void retranslateUi(QMainWindow *Cell_Main)
    {
        Cell_Main->setWindowTitle(QCoreApplication::translate("Cell_Main", "\346\226\207\344\273\266\347\256\241\347\220\206\345\231\250", nullptr));
        lib_search->setText(QCoreApplication::translate("Cell_Main", "\346\220\234\347\264\242\346\241\206", nullptr));
        btn_upload->setText(QCoreApplication::translate("Cell_Main", "\344\270\212\344\274\240", nullptr));
        btn_del->setText(QCoreApplication::translate("Cell_Main", "\345\210\240\351\231\244", nullptr));
        btn_open->setText(QCoreApplication::translate("Cell_Main", "\346\211\223\345\274\200\346\226\207\344\273\266\346\211\200\345\234\250\346\226\207\344\273\266\345\244\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cell_Main: public Ui_Cell_Main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELL_MAIN_H
