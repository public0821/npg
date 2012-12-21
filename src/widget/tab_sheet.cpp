/*
 * tab_sheet.cpp
 *
 *  Created on: 2011-8-22
 *      Author: Young <public0821@gmail.com>
 */
#include "tab_sheet.h"

#include <QSpacerItem>
#include <QVBoxLayout>
#include "send_thread.h"
#include <qmessagebox.h>
#include "base_protocol/udp_widget.h"
#include "base_protocol/tcp_widget.h"
#include "npg_define.h"
#include "base_protocol/ip_widget.h"
#include "base_protocol/ethernet_widget.h"

TabSheet::TabSheet(const QString& protocol_name
		, QWidget *parent
		, QString base_protocol_name
		, QString base_protocol_param)
:
		QWidget(parent)
				, m_protocol_name(protocol_name)
				, m_base_protocol_widget(NULL)
{
	m_send_thread = new SendThread(this);

	if (base_protocol_name == K_PROTOCOL_UDP) {
		m_base_protocol_widget = new UdpWidget(m_protocol_name, this);
	}
	else if (base_protocol_name == K_PROTOCOL_TCP) {
		m_base_protocol_widget = new TcpWidget(m_protocol_name, this);
	}
	else if (base_protocol_name == K_PROTOCOL_IP) {
		m_base_protocol_widget = new IpWidget(m_protocol_name, base_protocol_param, this);
	}
	else if (base_protocol_name == K_PROTOCOL_ETHERNET) {
		m_base_protocol_widget = new EthernetWidget(m_protocol_name, base_protocol_param, this);
	}
}

TabSheet::~TabSheet()
{
	if (m_send_thread->isRunning())
	{
		m_send_thread->stop();
		m_send_thread->wait();
	}
	delete m_send_thread;
}

void TabSheet::setupUi(QHBoxLayout* layout)
		{
	QHBoxLayout* simple_layout = new QHBoxLayout();

	m_send_button = new QPushButton(tr("Send"));
	m_advanced_button = new QPushButton(tr("Advanced"));
	m_tip_label = new QLabel();
	m_status_label1 = new QLabel();
	m_status_label2 = new QLabel();
	QSpacerItem *horizontal_spacer = new QSpacerItem(40, 20,
			QSizePolicy::Expanding, QSizePolicy::Minimum);

	simple_layout->addWidget(m_tip_label);
	simple_layout->addWidget(m_status_label1);
	simple_layout->addWidget(m_status_label2);
	simple_layout->addItem(horizontal_spacer);
	simple_layout->addWidget(m_advanced_button);
	simple_layout->addWidget(m_send_button);

	m_advanced_group = new QGroupBox(tr("advance:"));
//	m_advanceGroup->setStyleSheet("margin:5px 0px 0px 5px;padding:10px;border:3px solid red;border-radius:5px");
//	QString oldStyleSheet = m_advanceGroup->styleSheet();
	QHBoxLayout* advance_layout = new QHBoxLayout(m_advanced_group);
	advance_layout->addWidget(new QLabel(tr("Sendtype:")));
	m_send_typeBox = new QComboBox();
	m_send_typeBox->addItem(tr("Total"), QVariant((int) E_SEND_TYPE_TOTAL));
	m_send_typeBox->addItem(tr("Per second"), QVariant((int) E_SEND_TYPE_SPEED));
	advance_layout->addWidget(m_send_typeBox);
	advance_layout->addWidget(new QLabel(tr("Count:")));
	m_count_edit = new QLineEdit();
	advance_layout->addWidget(m_count_edit);
	advance_layout->addItem(
			new QSpacerItem(40, 20, QSizePolicy::Expanding,
					QSizePolicy::Minimum));

	QVBoxLayout* vboxlayout = new QVBoxLayout();
	vboxlayout->addWidget(m_advanced_group);
	vboxlayout->addLayout(simple_layout);
	layout->addLayout(vboxlayout);
//	layout->addWidget(m_sendButton);
	m_advanced_group->setVisible(false);
	m_is_advanced = false;

	connect(m_send_button, SIGNAL(released(void)), this, SLOT(onSend(void)));
//	connect(m_advanceButton, SIGNAL(toggled(bool)), m_advanceGroup, SLOT(setVisible(bool)));
	connect(m_advanced_button, SIGNAL(released(void)), this,
			SLOT(onAdvanced(void)));
	connect(m_send_thread, SIGNAL(finished(void)), this,
			SLOT(onSendFinish(void)));
	connect(m_send_thread, SIGNAL(counter(int, time_t)), this,
			SLOT(onCounter(int, time_t)));

	restoreSettings();
}

void TabSheet::showFailedTip(const QString& tip)
		{
	showTip(QString("<font color=red>%1</font>").arg(tip));
}

void TabSheet::showSuccessTip(const QString& tip)
		{
	showTip(QString("<font color=green>%1</font>").arg(tip));
}

void TabSheet::showTip(const QString& tip)
		{
	if (m_tip_label != NULL)
			{
		m_tip_label->setText(tip);
	}
}

void TabSheet::onAdvanced()
{

	if (m_is_advanced)
	{
		m_advanced_group->setVisible(false);
		m_advanced_button->setText(tr("Advanced"));
		m_is_advanced = !m_is_advanced;
	}
	else
	{
		m_advanced_group->setVisible(true);
		m_advanced_button->setText(tr("Simple"));
		m_is_advanced = !m_is_advanced;
	}
}

void TabSheet::onSend()
{
	m_tip_label->setText("");
	m_status_label1->setText("");
	m_status_label2->setText("");

	saveSettings();
	if (m_send_thread->isRunning()) { //running
		m_send_button->setText(tr("Send"));
		m_send_thread->stop();
		m_send_thread->wait();
		return;
	}

	//not running
	if (m_is_advanced) { //multi
		int index = m_send_typeBox->currentIndex();
		int count = m_count_edit->text().toInt();
//		QMessageBox::information(this, "test", QString("%1").arg(count));
		if (count == 0) {
			showFailedTip(tr("please input a valid count"));
			return;
		}
		m_send_button->setText(tr("stop"));
		m_send_thread->start((ESendType) m_send_typeBox->itemData(index).toInt(), count);
	}
	else { //single
		m_send_button->setEnabled(false);
		bool ret = preSendData();
		if (!ret) {
			showFailedTip();
			goto END;
		}

		ret = sendData();
		if (!ret) {
			postSendData();
			showFailedTip();
			goto END;
		}

		ret = postSendData();
		if (!ret) {
			showFailedTip();
			goto END;
		} else {
			showSuccessTip();
		}

		END:
		m_send_button->setEnabled(true);
	}
}

void TabSheet::onSendFinish() {
	const QString& error = m_send_thread->error();
	if (error.isEmpty()) { //thread exit successful
		showSuccessTip(tr("finished"));
	}
	else {
		showFailedTip(error);
	}

	m_send_button->setText(tr("Send"));

}

void TabSheet::onCounter(int count, time_t seconds) {
	m_status_label1->setText(QString(tr("total(time):%1(%2)")).arg(count).arg(seconds));
	double speed = 0;
	if (seconds == 0) {
		speed = count;
	} else {
		speed = (double) count / seconds;
	}
	m_status_label2->setText(QString(tr("speed:%1")).arg(speed));
}
