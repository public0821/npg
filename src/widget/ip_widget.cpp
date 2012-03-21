#include "ip_widget.h"
#include "npg_define.h"
#include "socket/ip.h"
#include <qsettings.h>
#include "system/types.h"
#include "socket/socket_public.h"

IpWidget::IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent)
	: BaseProtocolWidget(protocol_name, parent), m_ip(NULL)
{
	ui.setupUi(this);

	m_built_in_protocol.insert(std::make_pair(K_PROTOCOL_ICMP, (int)IPPROTO_ICMP));
	m_built_in_protocol.insert(std::make_pair(K_PROTOCOL_UDP, (int)IPPROTO_UDP));
	m_built_in_protocol.insert(std::make_pair(K_PROTOCOL_TCP, (int)IPPROTO_TCP));

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

QString IpWidget::preSendData()
{
	if (m_ip != NULL)
	{
		return tr("'preSendData' function has been called");//this message just for developer, End-user will not see it
	}

	int index = ui.protocol_box->findText(ui.protocol_box->currentText());
	int protocol = 0;
	if (index == -1)
	{
		protocol = ui.protocol_box->currentText().toInt();
	}
	else
	{
		protocol = ui.protocol_box->itemData(index).toInt();
	}

	m_dstip = ui.ip_edit->text().toLocal8Bit().constData();

	if (m_dstip.empty() || protocol == 0 )
	{
		return tr("ip and protocol must set");
	}

	m_ip = new Ip(protocol);

	return QString();
}

QString IpWidget::postSendData()
{
	if (m_ip != NULL)
	{
		delete m_ip;
		m_ip = NULL;
	}

	return QString();
}

QString IpWidget::sendData(const char* data, u_int16_t length)
{
	if (m_ip == NULL)
	{
		return tr("should call 'preSendData' function first");
	}

	bool ret = m_ip->sendto(m_dstip.c_str(), data, length);
	if (!ret)
	{
		return QString(m_ip->errorString());
	}

	return QString();
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
