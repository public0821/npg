#include "npg.h"

#include <QtGui>
#include <QApplication>
#include <qtextcodec.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    npg w;
    w.show();
    return a.exec();
}
