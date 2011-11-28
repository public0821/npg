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

DnsWidget::DnsWidget(QWidget *parent) :
		TabSheet(parent)
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
	settings.beginGroup(K_DNS);
	settings.setValue("server", ui.server_edit->text());
	settings.setValue("request", ui.request_edit->text());
	settings.setValue("reverse", (int)ui.reverse_checkbox->checkState());
	settings.endGroup();
}

void DnsWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_DNS);
	ui.server_edit->setText(settings.value("server").toString());
	ui.request_edit->setText(settings.value("request").toString());
	ui.reverse_checkbox->setCheckState((Qt::CheckState)settings.value("reverse").toInt());
	settings.endGroup();
}

QString DnsWidget::sendData()
{
	std::string ip = ui.server_edit->text().toStdString();
	std::string request = ui.request_edit->text().toStdString();
	EDnsRequestType type = E_DNS_A;
	if(ui.reverse_checkbox->checkState() == Qt::Checked)
	{
		type = E_DNS_PTR;
	}

	Dns dns;

	dns.sendto(ip.c_str(), request.c_str(), type);

	return dns.errorStr();
}
