#include "npg.h"

#include <QtGui>
#include <QApplication>
#include <qtextcodec.h>
#include <qmessagebox.h>
#ifdef _MSC_VER
	#include <winsock2.h>
#endif
#ifdef __GNUC__
	#include <signal.h>
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));//("UTF-8"));
#ifdef _MSC_VER
	WSADATA wsaData;
	int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		QMessageBox::about(NULL, QObject::tr("tip"), QString(QObject::tr("WSAStartup failed with error: %1")).arg(err));
		return -1;
	}
#endif
#ifdef __GNUC__
	struct   sigaction   sa; 
	sa.sa_handler   =   SIG_IGN; 
	sigaction(   SIGPIPE,   &sa,   0   );
#endif
    npg w;
    w.show();
    int ret = a.exec();
#ifdef _MSC_VER
	WSACleanup();
#endif

	return ret;
}
