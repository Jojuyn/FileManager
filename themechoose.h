#ifndef THEMECHOOSE_H
#define THEMECHOOSE_H

#include <QWidget>

namespace Ui {
class ThemeChoose;
}

class ThemeChoose : public QWidget
{
    Q_OBJECT

public:
    explicit ThemeChoose(QWidget *parent = nullptr);
    ~ThemeChoose();
    Ui::ThemeChoose *ui;
};

#endif // THEMECHOOSE_H
