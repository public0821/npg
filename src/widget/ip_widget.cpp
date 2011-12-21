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

	std::map<sstring, int>::const_iterator it_find;
	it_find = m_built_in_protocol.find(ip_protocol_name.toStdString());
	if (it_find != m_built_in_protocol.end())
	{
		ui.protocol_edit->setVisible(false);
		ui.checkbox->setVisible(false);
		ui.protocol_box->addItem(it_find->first.c_str(), QVariant(it_find->second));
	}
	else
	{
		ui.protocol_edit->setValidator(new QIntValidator(1, 254, this));
		std::map<sstring, int>::const_iterator it;
		it = m_built_in_protocol.begin();
		for (; it != m_built_in_protocol.end(); ++it)
		{
			ui.protocol_box->addItem(it->first.c_str(), QVariant(it->second));
		}
		ui.protocol_box->setEditable(false);

		connect(ui.checkbox, SIGNAL(clicked ( bool)), ui.protocol_box,
			SLOT( setHidden(bool)));
		connect(ui.checkbox, SIGNAL(clicked ( bool)), ui.protocol_edit,
			SLOT( setVisible(bool)));
		ui.protocol_edit->setVisible(false);
	}

}

IpWidget::~IpWidget()
{

}

QString IpWidget::sendData(const char* data, u_int16_t length)
{
	int protocol = 0;
	if (ui.protocol_box->isVisible())
	{
		protocol = ui.protocol_box->itemData(ui.protocol_box->currentIndex()).toInt();
	}
	else
	{
		protocol = ui.protocol_edit->text().toInt();
	}
	
	sstring ip_str = ui.ip_edit->text().toStdString();

	if (ip_str.empty() || protocol == 0 )
	{
		return tr("ip and protocol must set");
	}

	Ip ip(protocol);
	bool ret = ip.sendto(ip_str.c_str(), data, length);
	if (!ret)
	{
		return QString(tr(ip.errorStr()));
	}

	return QString();
}

void IpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	settings.setValue("ip", ui.ip_edit->text());
	settings.setValue("protocol", ui.protocol_box->currentText());
	settings.endGroup();
}

void IpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	ui.ip_edit->setText(settings.value("ip").toString());
	ui.protocol_box->setEditText(settings.value("protocol").toString());
	settings.endGroup();
}
