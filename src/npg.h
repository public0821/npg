#ifndef NPG_H
#define NPG_H

#include <QtGui/QMainWindow>
#include "ui_npg.h"

class npg : public QMainWindow
{
    Q_OBJECT

public:
    npg(QWidget *parent = 0);
    ~npg();

private:
    Ui::npgClass ui;
};

#endif // NPG_H
