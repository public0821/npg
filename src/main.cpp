#include "npg.h"

#include <QtGui>
#include <QApplication>
#include <qtextcodec.h>
#include <qmessagebox.h>
#ifdef WIN32
	#include <winsock2.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));//("UTF-8"));
#ifdef WIN32
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		QMessageBox::about(NULL, QObject::tr("tip"), QString(QObject::tr("WSAStartup failed with error: %1")).arg(err));
		return -1;
	}
#endif
    npg w;
    w.show();
    int ret = a.exec();
#ifdef WIN32
	WSACleanup();
#endif

	return ret;
}
