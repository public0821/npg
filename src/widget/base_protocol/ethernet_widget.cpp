#include "ethernet_widget.h"
#include "../logger.h"
#include "lib/socket/toolkit.h"
#include <qsettings.h>
#include "npg_define.h"
#include "lib/socket/ethernet.h"

Q_DECLARE_METATYPE(ifi_info)

EthernetWidget::EthernetWidget(const QString& protocol_name, const QString& ether_protocol_name, QWidget *parent) :
		BaseProtocolWidget(protocol_name, parent), m_ethernet(NULL) {
	ui.setupUi(this);
	setupInterface(parent);
	setupEtherProtocol(ether_protocol_name);
	connect(ui.interface_box, SIGNAL(currentIndexChanged (int)), this, SLOT(onInterfaceChanged(int)));
}

EthernetWidget::~EthernetWidget() {

}

bool EthernetWidget::preSendData() {
	if (m_ethernet != NULL) {
		//this message just for developer, End-user will not see it
		LOG_ERROR( tr("'preSendData' function has been called"));
		return false;
	}
	m_ethernet = new Ethernet();
	int index = ui.protocol_box->currentIndex();
	m_protocol = ui.protocol_box->itemData(index).toInt();
	m_dstmac = ui.to_mac_edit->text().toLocal8Bit().constData();
	m_srcmac = ui.from_mac_edit->text().toLocal8Bit().constData();

	index = ui.interface_box->currentIndex();
	m_dev = ui.interface_box->itemData(index).value<ifi_info>();
	return true;
}

bool EthernetWidget::postSendData() {
	if (m_ethernet != NULL) {
		delete m_ethernet;
		m_ethernet = NULL;
	}
	return true;
}

bool EthernetWidget::sendData(const char* data, uint16_t length) {
	if (m_ethernet == NULL) {
		LOG_ERROR( tr("should call 'preSendData' function first"));
		return false;
	}

	return m_ethernet->sendto(m_dev, m_dstmac.c_str(), m_srcmac.c_str(), m_protocol, data, length);
}

void EthernetWidget::saveSettings() {
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	settings.setValue("ether_interface", ui.interface_box->currentIndex());
	settings.setValue("ether_to_mac", ui.to_mac_edit->text());
	settings.setValue("ether_from_mac", ui.from_mac_edit->text());
	settings.setValue("ether_protocol", ui.protocol_box->currentText());
	//	int index = ui.operationBox->currentIndex();
	//		int op = ui.operationBox->itemData(index).toInt();
	settings.endGroup();
}
void EthernetWidget::restoreSettings() {
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	ui.interface_box->setCurrentIndex(settings.value("ether_interface").toInt());
	ui.to_mac_edit->setText(settings.value("ether_to_mac").toString());
	ui.from_mac_edit->setText(settings.value("ether_from_mac").toString());
	ui.protocol_box->setEditText(settings.value("ether_protocol").toString());
	settings.endGroup();
}

void EthernetWidget::setupEtherProtocol(const QString& ether_protocol_name) {
	std::map<QString, int> built_in_protocol;
	built_in_protocol.insert(std::make_pair(K_PROTOCOL_IP, (int) ETH_P_IP));
	built_in_protocol.insert(std::make_pair(K_PROTOCOL_ARP, (int) ETH_P_ARP));
	built_in_protocol.insert(std::make_pair(K_PROTOCOL_RARP, (int) ETH_P_RARP));

	std::map<QString, int>::const_iterator it_find;
	it_find = built_in_protocol.find(ether_protocol_name);
	if (it_find != built_in_protocol.end()) {
		QString text = QString("%1 (%2)").arg(it_find->first).arg(it_find->second);
		ui.protocol_box->addItem(text, QVariant(it_find->second));
		ui.protocol_box->setEditable(false);
	} else {
		std::map<QString, int>::const_iterator it;
		it = built_in_protocol.begin();
		for (; it != built_in_protocol.end(); ++it) {
			QString text = QString("%1 (%2)").arg(it->first).arg(it->second);
			ui.protocol_box->addItem(text, QVariant(it->second));
		}
		ui.protocol_box->setEditable(true);
	}
}

void EthernetWidget::setupInterface(QWidget *parent) {
	SocketToolkit toolkit;
	std::vector<ifi_info> ifiInfos = toolkit.ifiInfo();
	if (ifiInfos.size() == 0) {
		LOG_ERROR(tr("get ifi info failed"));
	}

	std::vector<ifi_info>::iterator it;
	int index = 0;
	for (it = ifiInfos.begin(); it != ifiInfos.end(); ++it) {
		index++;
#ifdef __GNUC__
		if (it->ifi_flags & IFF_LOOPBACK) // ignore loopback
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
		toolkit.macToString((const uint8_t *) it->ifi_haddr, mac, sizeof(mac));
		it->ifi_index = index;
		ui.interface_box->addItem(
				QString("%1-%2-%3").arg(it->ifi_name).arg(ip).arg(mac),
				QVariant::fromValue(*it));
	}
}

void EthernetWidget::onInterfaceChanged(int index) {
	ifi_info dev = ui.interface_box->itemData(index).value<ifi_info>();
	char mac[256];
	SocketToolkit toolkit;
	toolkit.macToString((const uint8_t *) dev.ifi_haddr, mac, sizeof(mac));

	ui.from_mac_edit->setText(mac);
}
