/*
 * udp_widget.cpp
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */
#include "data_tab_sheet.h"
#include <qmessagebox.h>
#include <qsettings.h>
#include <string>
#include "npg_define.h"
#include "lib/socket/udp.h"
#include "lib/socket/raw_udp.h"
#include "../logger.h"

DataTabSheet::DataTabSheet(const QString& name, QWidget *parent) :
		TabSheet(name, parent, name)
{
	setupUi();
}

DataTabSheet::~DataTabSheet()
{
}

bool DataTabSheet::preSendData()
{
	QString data = m_data_edit->toPlainText();
	if (data.isEmpty())
	{
		LOG_ERROR(tr("ip and port and data must set"));
		return false;
	}
	m_data = data.toLocal8Bit();

	return dependProtocolWidget()->preSendData();
}

bool DataTabSheet::postSendData()
{
	m_data.clear();
	return dependProtocolWidget()->postSendData();
}

bool DataTabSheet::sendData()
{
	return dependProtocolWidget()->sendData(m_data.constData(), m_data.size());
}

void DataTabSheet::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	settings.setValue("data", m_data_edit->toPlainText());
	settings.endGroup();

	TabSheet::saveSettings();
}

void DataTabSheet::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(protocolName());
	m_data_edit->setText(settings.value("data").toString());
	settings.endGroup();

	TabSheet::restoreSettings();
}

void DataTabSheet::setupUi()
{
	QGridLayout* gridLayout = new QGridLayout(this);
	gridLayout->setSpacing(6);
	gridLayout->setContentsMargins(11, 11, 11, 11);
	gridLayout->setObjectName("gridLayout_2");

	gridLayout->addWidget(dependProtocolWidget(), 0, 0, 1, 1);

	m_data_edit = new QTextEdit(this);
	m_data_edit->setObjectName("data_edit");

	gridLayout->addWidget(m_data_edit, 1, 0, 1, 1);

	QHBoxLayout* send_layout = new QHBoxLayout();
	send_layout->setSpacing(6);
	send_layout->setObjectName("send_layout");
	gridLayout->addLayout(send_layout, 2, 0, 1, 1);

	TabSheet::setupUi(send_layout);
} // setupUi
