#include "udp_widget.h"
#include <qmessagebox.h>
#include <string>
#include "socket/udp.h"

UdpWidget::UdpWidget(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
//	QSize size = parent->size();
//	setGeometry(0, 0, size.width(), size.height());
//	ui.gridLayoutWidget->setGeometry(0, 0, size.width(), size.height());
	connect(ui.pushButton, SIGNAL(released(void)), this, SLOT(onSend(void)));
}

UdpWidget::~UdpWidget()
{

}


void UdpWidget::onSend()
{
	std::string ip = ui.ipEdit->text().toStdString();
	int port = ui.portEdit->text().toInt();
	std::string data = ui.dataEdit->toPlainText().toStdString();

	Udp udp;
	udp.send(ip.c_str(), port, data.c_str(), data.length());

	QMessageBox::information(this, "test", "test");
}
