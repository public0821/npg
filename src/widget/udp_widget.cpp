/*
 * udp_widget.cpp
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */
#include "udp_widget.h"
#include <qmessagebox.h>
#include <qsettings.h>
#include <string>
#include "npg_define.h"
#include "socket/udp.h"
#include "socket/raw_udp.h"

UdpWidget::UdpWidget(QWidget *parent) :
		TabSheet(parent)
{
	ui.setupUi(this);
//	ui.labelTip->setTextFormat(Qt::RichText);
//	QSize size = parent->size();
//	setGeometry(0, 0, size.width(), size.height());
//	ui.gridLayoutWidget->setGeometry(0, 0, size.width(), size.height());
	setupUi(ui.send_layout);

	ui.src_port_edit->setValidator(new QIntValidator(1, 65535, this));
	ui.dst_port_edit->setValidator(new QIntValidator(1, 65535, this));

	connect(ui.src_ip_box, SIGNAL(clicked ( bool)), ui.src_ip_edit,
			SLOT( setDisabled(bool)));
	connect(ui.src_ip_box, SIGNAL(clicked ( bool)), ui.src_port_edit,
				SLOT( setDisabled(bool)));

	ui.src_ip_box->setChecked(true);
	ui.src_ip_edit->setDisabled(true);
	ui.src_port_edit->setDisabled(true);
}

UdpWidget::~UdpWidget()
{
}

QString UdpWidget::sendData()
{

	std::string dstip = ui.dst_ip_edit->text().toStdString();
	u_int16_t dstport = ui.dst_port_edit->text().toUShort();
	std::string data = ui.data_edit->toPlainText().toStdString();
	if (dstip.empty() || dstport <= 0 || data.empty())
	{
		return tr("ip and port and data must set");
	}

	bool is_raw_socket = !(ui.src_ip_box->checkState() == Qt::Checked);
	if (is_raw_socket)
	{
		std::string srcip = ui.src_ip_edit->text().toStdString();
		u_int16_t srcport = ui.src_port_edit->text().toUShort();
		RawUdp raw_udp;
		bool ret = raw_udp.sendto(srcip.c_str(), dstip.c_str(), srcport, dstport,
				data.c_str(), data.length());
		if (!ret)
		{
			return QString(tr(raw_udp.errorStr()));
		}
	}
	else
	{

		Udp udp;
		bool ret = udp.sendto(dstip.c_str(), dstport, data.c_str(),
				data.length());
		if (!ret)
		{
			return QString(tr(udp.errorStr()));
		}
	}
	return QString();
}

void UdpWidget::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_UDP);
	settings.setValue("srcip", ui.src_ip_edit->text());
	settings.setValue("dstip", ui.dst_ip_edit->text());
	settings.setValue("srcport", ui.src_port_edit->text());
	settings.setValue("dstport", ui.dst_port_edit->text());
	settings.setValue("data", ui.data_edit->toPlainText());
	settings.endGroup();
}

void UdpWidget::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(K_UDP);
	ui.src_ip_edit->setText(settings.value("srcip").toString());
	ui.dst_ip_edit->setText(settings.value("dstip").toString());
	ui.src_port_edit->setText(settings.value("srcport").toString());
	ui.dst_port_edit->setText(settings.value("dstport").toString());
	ui.data_edit->setText(settings.value("data").toString());
	settings.endGroup();
}
