#include "ip_widget.h"
#include "npg_define.h"
#include "lib/socket/ip.h"
#include <qsettings.h>
#include "lib/types.h"
#include "../logger.h"
#include "lib/socket/socket.h"

IpWidget::IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent)
:
		BaseProtocolWidget(protocol_name, parent), m_ip(NULL)
{
	ui.setupUi(this);

	m_built_in_protocol.insert(std::make_pair(K_PROTOCOL_ICMP, (int) IPPROTO_ICMP));
	m_built_in_protocol.insert(std::make_pair(K_PROTOCOL_UDP, (int) IPPROTO_UDP));
	m_built_in_protocol.insert(std::make_pair(K_PROTOCOL_TCP, (int) IPPROTO_TCP));

	std::map<QString, int>::const_iterator it_find;
	it_find = m_built_in_protocol.find(ip_protocol_name);
	if (it_find != m_built_in_protocol.end())
			{
		QString text = QString("%1 (%2)").arg(it_find->first).arg(it_find->second);
		ui.protocol_box->addItem(text, QVariant(it_find->second));
		ui.protocol_box->setEditable(false);
	}
	else
	{
		std::map<QString, int>::const_iterator it;
		it = m_built_in_protocol.begin();
		for (; it != m_built_in_protocol.end(); ++it)
		{
			QString text = QString("%1 (%2)").arg(it->first).arg(it->second);
			ui.protocol_box->addItem(text, QVariant(it->second));
		}
		ui.protocol_box->setEditable(true);
	}

}

IpWidget::~IpWidget()
{

}

bool IpWidget::preSendData()
{
	if (m_ip != NULL) {
		LOG_ERROR(tr("'preSendData' function has been called"));
		return false;
	}

	int index = ui.protocol_box->findText(ui.protocol_box->currentText());
	int protocol = 0;
	if (index == -1) {
		protocol = ui.protocol_box->currentText().toInt();
	}
	else
	{
		protocol = ui.protocol_box->itemData(index).toInt();
	}

	std::string dstip = ui.ip_edit->text().toLocal8Bit().constData();

	if (dstip.empty() || protocol == 0) {
		LOG_ERROR(tr("ip and protocol must set"));
		return false;
	}

	if (!m_dstip.from_string(dstip)) {
		LOG_ERROR(tr("invaild ip: %1").arg(dstip.c_str()));
		return false;
	}

	m_ip = new Ip(protocol);

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

	return m_ip->sendto(m_dstip, data, length);
}

void IpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	settings.setValue("ip", ui.ip_edit->text());
	settings.setValue("protocol", ui.protocol_box->currentText());
//	settings.setValue("protocol_index", ui.protocol_box->currentIndex());
	settings.endGroup();
}

void IpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	ui.ip_edit->setText(settings.value("ip").toString());
	ui.protocol_box->setEditText(settings.value("protocol").toString());
//	ui.protocol_box->setCurrentIndex(settings.value("protocol_index").toInt());
	settings.endGroup();
}
