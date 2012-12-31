#include "ip_widget.h"
#include "config.h"
#include "lib/socket/ip.h"
#include <qsettings.h>
#include "lib/types.h"
#include "../logger.h"
#include "lib/socket/socket.h"

const static char K_IP_UDP[] = "UDP";
const static char K_IP_TCP[] = "TCP";
const static char K_IP_ICMP[] = "ICMP";
const static char K_IP_IGMP[] = "IGMP";

IpWidget::IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent)
:
		BaseProtocolWidget(protocol_name, parent), m_ip(NULL) {
	ui.setupUi(this);

	m_built_in_protocol.insert(std::make_pair(K_IP_IGMP, (int) IPPROTO_IGMP));
	m_built_in_protocol.insert(std::make_pair(K_IP_ICMP, (int) IPPROTO_ICMP));
	m_built_in_protocol.insert(std::make_pair(K_IP_UDP, (int) IPPROTO_UDP));
	m_built_in_protocol.insert(std::make_pair(K_IP_TCP, (int) IPPROTO_TCP));

	std::map<QString, int>::const_iterator it_find;
	it_find = m_built_in_protocol.find(ip_protocol_name);
	if (it_find != m_built_in_protocol.end()) {
		ui.protocol_box->addItem(it_find->second, it_find->first);
		ui.protocol_box->setEditable(false);
	} else {
		std::map<QString, int>::const_iterator it;
		it = m_built_in_protocol.begin();
		for (; it != m_built_in_protocol.end(); ++it) {
			ui.protocol_box->addItem(it->second, it->first);
			ui.protocol_box->setEditable(false);
		}
		ui.protocol_box->setEditable(true);
	}

	connect(ui.default_box, SIGNAL(clicked ( bool)), ui.sip_box,
			SLOT( setDisabled(bool)));

	ui.dip_edit->setToolTip(tr("Multiple IP separated by commas"));

}

IpWidget::~IpWidget() {

}

bool IpWidget::preSendData() {
	if (m_ip != NULL) {
		LOG_ERROR(tr("'preSendData' function has been called"));
		return false;
	}

	int protocol = ui.protocol_box->getIntStrValue().toInt();

	QString all_dstip = ui.dip_edit->text();
	QStringList dstip_list = all_dstip.split(',');
	m_dstip.clear();
	for (int i = 0; i < dstip_list.size(); i++) {
		std::string dstip = dstip_list[i].toLocal8Bit().constData();
		if (dstip.empty()) {
			continue;
		}
		IpAddress addr;
		bool ret = addr.from_string(dstip);
		if (!ret) {
			LOG_ERROR(tr("invaild dst ip: %1").arg(dstip.c_str()));
			return false;
		}
		m_dstip.push_back(addr);
	}

	if (m_dstip.size() == 0 || protocol == 0) {
		LOG_ERROR(tr("ip and protocol must set"));
		return false;
	}

	if (ui.default_box->checkState() == Qt::Checked) {
		m_ip = new Ip(protocol);
	} else {
		IpAddress src_addr = ui.sip_box->getIpAddress();
		m_ip = new Ip(protocol, src_addr);
	}

	return true;
}

bool IpWidget::postSendData()
{
	if (m_ip != NULL) {
		delete m_ip;
		m_ip = NULL;
	}

	return true;
}

bool IpWidget::sendData(const char* data, uint16_t length) {
	if (m_ip == NULL) {
		LOG_ERROR(tr("should call 'preSendData' function first"));
		return false;
	}

	for (size_t i = 0; i < m_dstip.size(); i++) {
		bool ret = m_ip->sendto(m_dstip.at(i), data, length);
		if (!ret) {
			return false;
		}
	}

	return true;
}

void IpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	settings.setValue("dip", ui.dip_edit->text());
	settings.setValue("protocol", ui.protocol_box->currentText());
	settings.setValue("sip", ui.sip_box->currentIndex());
	settings.setValue("default_box", ui.default_box->checkState());
	settings.endGroup();
}

void IpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(fullProtocolName());
	ui.dip_edit->setText(settings.value("dip").toString());
	ui.protocol_box->setEditText(settings.value("protocol").toString());
	ui.sip_box->setCurrentIndex(settings.value("sip").toInt());
	Qt::CheckState state = (Qt::CheckState) settings.value("default_box").toInt();
	if (state == Qt::Checked) {
		ui.default_box->click();
	}
	settings.endGroup();
}
