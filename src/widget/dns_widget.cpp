/*
 * dns_widget.cpp
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */


#include "dns_widget.h"
#include <qsettings.h>
#include "npg_define.h"
#include "protocol/dns.h"

DnsWidget::DnsWidget(const QString& name,QWidget *parent) :
		TabSheet(name, parent)
{
	ui.setupUi(this);
	setupUi(ui.advanced_layout);
}

DnsWidget::~DnsWidget()
{

}

void DnsWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	settings.setValue("server", ui.server_edit->text());
	settings.setValue("request", ui.request_edit->text());
	settings.setValue("reverse", (int)ui.reverse_checkbox->checkState());
	settings.endGroup();
}

void DnsWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	ui.server_edit->setText(settings.value("server").toString());
	ui.request_edit->setText(settings.value("request").toString());
	ui.reverse_checkbox->setCheckState((Qt::CheckState)settings.value("reverse").toInt());
	settings.endGroup();
}

QString DnsWidget::sendData()
{
	sstring ip = ui.server_edit->text().toStdString();
	sstring request = ui.request_edit->text().toStdString();
	EDnsRequestType type = E_DNS_REQUEST_TYPE_A;
	if(ui.reverse_checkbox->checkState() == Qt::Checked)
	{
		type = E_DNS_REQUEST_TYPE_PTR;
	}

	Dns dns;

	dns.sendto(ip.c_str(), request.c_str(), type);

	return dns.errorStr();
}
