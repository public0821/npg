#include "npg.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    npg w;
    w.show();
    return a.exec();
}
