#include "ip_widget.h"
#include "npg_define.h"
#include "socket/ip.h"
#include <qsettings.h>
#include "system/types.h"
#include "socket/socket_public.h"

IpWidget::IpWidget(const QString& protocol_name, const QString& ip_protocol_name, QWidget *parent)
	: BaseProtocolWidget(protocol_name, parent)
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

QString IpWidget::sendData(const char* data, u_int16_t length)
{
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
	
	sstring ip_str = ui.ip_edit->text().toLocal8Bit().constData();

	if (ip_str.empty() || protocol == 0 )
	{
		return tr("ip and protocol must set");
	}

	Ip ip(protocol);
	bool ret = ip.sendto(ip_str.c_str(), data, length);
	if (!ret)
	{
		return QString(ip.errorString());
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
