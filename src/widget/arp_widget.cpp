/*
 * arp_widget.cpp
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */
#include "arp_widget.h"
#include "socket/arp.h"
#include <string>
#include <qsettings.h>
#include "npg_define.h"
#include "socket/socket_toolkit.h"

const int K_OP_ARP_REQUEST = 1;
const int K_OP_ARP_RESPONSE = 2;
const int K_OP_RARP_REQUEST = 3;
const int K_OP_RARP_RESPONSE = 4;

Q_DECLARE_METATYPE(ifi_info)

ArpWidget::ArpWidget(const QString& name, QWidget *parent) :
		TabSheet(name, parent)
{
	ui.setupUi(this);
	setupUi(ui.send_layout);

	ui.operation_box->addItem(tr("ARP Request"), QVariant(K_OP_ARP_REQUEST));
	ui.operation_box->addItem(tr("ARP Response"), QVariant(K_OP_ARP_RESPONSE));
	ui.operation_box->addItem(tr("RARP Request"), QVariant(K_OP_RARP_REQUEST));
	ui.operation_box->addItem(tr("RARP Response"), QVariant(K_OP_RARP_RESPONSE));

	SocketToolkit toolkit;
	std::vector<ifi_info> ifiInfos = toolkit.ifiInfo();
	if(strlen(toolkit.errorStr()) > 0)
	{
		showFailedTip(toolkit.errorStr());
	}
	
	std::vector<ifi_info>::iterator it;
	int index = 0;
	for (it = ifiInfos.begin(); it != ifiInfos.end(); ++it)
	{
		index++;
#ifdef __GNUC__
		if (it->ifi_flags & IFF_LOOPBACK)// ignore loopback
		{
			continue;
		}
#endif		
		struct sockaddr_in * sin = (struct sockaddr_in *) &(it->ifi_addr);
		char ip[INET_ADDRSTRLEN];
		bzero(ip, sizeof(ip));
		//inet_ntop(AF_INET, &sin->sin_addr, ip, sizeof(ip));
		strncpy(ip, inet_ntoa(sin->sin_addr), sizeof(ip));
		char mac[256];
		bzero(mac, sizeof(mac));
		sprintf(mac, "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
				(u_int8_t) it->ifi_haddr[0], (u_int8_t) it->ifi_haddr[1],
				(u_int8_t) it->ifi_haddr[2], (u_int8_t) it->ifi_haddr[3],
				(u_int8_t) it->ifi_haddr[4], (u_int8_t) it->ifi_haddr[5]);
		it->ifi_index = index;
		ui.interface_box->addItem(
				QString("%1-%2-%3").arg(it->ifi_name).arg(ip).arg(mac),
				QVariant::fromValue(*it));
	}

}

ArpWidget::~ArpWidget()
{

}

void ArpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(name());
	settings.setValue("toMac", ui.to_mac_edit->text());
	settings.setValue("fromMac", ui.from_mac_edit->text());
	settings.setValue("sendMac", ui.send_mac_edit->text());
	settings.setValue("sendIp", ui.send_ip_edit->text());
	settings.setValue("recvMac", ui.recv_mac_edit->text());
	settings.setValue("recvIp", ui.recv_ip_edit->text());
//	int index = ui.operationBox->currentIndex();
//		int op = ui.operationBox->itemData(index).toInt();
	settings.endGroup();
}
void ArpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(name());
	ui.to_mac_edit->setText(settings.value("toMac").toString());
	ui.from_mac_edit->setText(settings.value("fromMac").toString());
	ui.send_mac_edit->setText(settings.value("sendMac").toString());
	ui.send_ip_edit->setText(settings.value("sendIp").toString());
	ui.recv_mac_edit->setText(settings.value("recvMac").toString());
	ui.recv_ip_edit->setText(settings.value("recvIp").toString());
	settings.endGroup();
}

QString ArpWidget::sendData()
{
	int index = ui.operation_box->currentIndex();
	int op = ui.operation_box->itemData(index).toInt();
	sstring to_mac = ui.to_mac_edit->text().toStdString();
	sstring from_mac = ui.from_mac_edit->text().toStdString();

	sstring send_mac = ui.send_mac_edit->text().toStdString();
	sstring send_ip = ui.send_ip_edit->text().toStdString();
	sstring recv_mac = ui.recv_mac_edit->text().toStdString();
	sstring recv_ip = ui.recv_ip_edit->text().toStdString();

	index = ui.interface_box->currentIndex();
	ifi_info dev = ui.interface_box->itemData(index).value<ifi_info>();
//	int adapter = ui.interface_box->itemData(index).toInt();

	Arp arp;
	arp.sendto(dev, to_mac.c_str(), from_mac.c_str(), op, send_mac.c_str(),
			send_ip.c_str(), recv_mac.c_str(), recv_ip.c_str());

	return arp.errorStr();
}
