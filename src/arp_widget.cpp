#include "arp_widget.h"
#include "tab_sheet.h"
#include "socket/arp.h"
#include <string>
#include <qsettings.h>
#include "public.h"
#include "socket/socket_toolkit.h"

const int K_OP_ARP_REQUEST = 1;
const int K_OP_ARP_RESPONSE = 2;
const int K_OP_RARP_REQUEST = 3;
const int K_OP_RARP_RESPONSE = 4;

ArpWidget::ArpWidget(QWidget *parent) :
		TabSheet(parent)
{
	ui.setupUi(this);
	setupUi(ui.sendLayout);

	ui.operationBox->addItem(tr("ARP Request"), QVariant(K_OP_ARP_REQUEST));
	ui.operationBox->addItem(tr("ARP Response"), QVariant(K_OP_ARP_RESPONSE));
	ui.operationBox->addItem(tr("RARP Request"), QVariant(K_OP_RARP_REQUEST));
	ui.operationBox->addItem(tr("RARP Response"), QVariant(K_OP_RARP_RESPONSE));

	SocketToolkit toolkit;
	std::vector<ifi_info> ifiInfos = toolkit.getIfiInfo();
	std::vector<ifi_info>::iterator it;
	int index = 0;
	for (it = ifiInfos.begin(); it != ifiInfos.end(); ++it)
	{
		index++;
		if (it->ifi_flags & IFF_LOOPBACK)
		{
			continue;
		}
		struct sockaddr_in * sin = (struct sockaddr_in *) &(it->ifi_addr);
		char ip[INET_ADDRSTRLEN];
		bzero(ip, sizeof(ip));
		inet_ntop(AF_INET, &sin->sin_addr, ip, sizeof(ip));
		char mac[256];
		bzero(mac, sizeof(mac));
		sprintf(mac, "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
				(uint8_t) it->ifi_haddr[0], (uint8_t) it->ifi_haddr[1],
				(uint8_t) it->ifi_haddr[2], (uint8_t) it->ifi_haddr[3],
				(uint8_t) it->ifi_haddr[4], (uint8_t) it->ifi_haddr[5]);
		ui.interfaceBox->addItem(
				QString("%1-%2-%3").arg(it->ifi_name).arg(ip).arg(mac),
				QVariant(index));
	}

}

ArpWidget::~ArpWidget()
{

}

void ArpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_ARP);
	settings.setValue("toMac", ui.toMacEdit->text());
	settings.setValue("fromMac", ui.fromMacEdit->text());
	settings.setValue("sendMac", ui.sendMacEdit->text());
	settings.setValue("sendIp", ui.sendIpEdit->text());
	settings.setValue("recvMac", ui.recvMacEdit->text());
	settings.setValue("recvIp", ui.recvIpEdit->text());
//	int index = ui.operationBox->currentIndex();
//		int op = ui.operationBox->itemData(index).toInt();
	settings.endGroup();
}
void ArpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_ARP);
	ui.toMacEdit->setText(settings.value("toMac").toString());
	ui.fromMacEdit->setText(settings.value("fromMac").toString());
	ui.sendMacEdit->setText(settings.value("sendMac").toString());
	ui.sendIpEdit->setText(settings.value("sendIp").toString());
	ui.recvMacEdit->setText(settings.value("recvMac").toString());
	ui.recvIpEdit->setText(settings.value("recvIp").toString());
	settings.endGroup();
}

QString ArpWidget::sendData()
{
	int index = ui.operationBox->currentIndex();
	int op = ui.operationBox->itemData(index).toInt();
	std::string toMac = ui.toMacEdit->text().toStdString();
	std::string fromMac = ui.fromMacEdit->text().toStdString();

	std::string sendMac = ui.sendMacEdit->text().toStdString();
	std::string sendIp = ui.sendIpEdit->text().toStdString();
	std::string recvMac = ui.recvMacEdit->text().toStdString();
	std::string recvIp = ui.recvIpEdit->text().toStdString();

	index = ui.interfaceBox->currentIndex();
	int interface = ui.interfaceBox->itemData(index).toInt();

	Arp arp;
	arp.sendto(interface, toMac.c_str(), fromMac.c_str(), op, sendMac.c_str(),
			sendIp.c_str(), recvMac.c_str(), recvIp.c_str());

	return arp.errorStr();
}
