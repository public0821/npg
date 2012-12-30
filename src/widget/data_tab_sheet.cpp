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
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include "config.h"
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
	if (data.isEmpty())	{
		LOG_ERROR(tr("ip and port and data must set"));
		return false;
	}

	if (m_default_encoding_box->checkState() == Qt::Checked)	{
		m_data = data.toLocal8Bit();
	}else{
		QTextCodec * codec = QTextCodec::codecForName(m_encoding_box->currentText().toStdString().c_str());
		m_data = codec->fromUnicode(data);
	}
	
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

	//m_load_config_button->setVisible(false);
	//m_save_config_button->setVisible(false);
} // setupUi




void DataTabSheet::onRestoreSettings(){
	QString file_name = QFileDialog::getOpenFileName(this, tr("Select file"), QDir::currentPath(), tr("all files (*)"));
	if (file_name.isEmpty()) {
		return;
	}

	QFile file(file_name);
	if (!file.open(QFile::ReadOnly )) {
		QString errorString = tr("Error: Cannot read file %1: %2");
		errorString = errorString.arg(file_name, file.errorString());
		QMessageBox::critical(NULL, tr("tip"), errorString);
		return;
	}

	QTextStream in(&file);

	m_data_edit->setText(in.readAll());
}

void DataTabSheet::onSaveSettings() {
	QString file_name = QFileDialog::getSaveFileName(this, tr("Select file"), QDir::currentPath(), tr("all files (*)"));
	if (file_name.isEmpty()) {
		return;
	}
	QFile file(file_name);
	file.open(QIODevice::WriteOnly);
	QTextStream t(&file);
	t << m_data_edit->toPlainText();
	file.close();

}