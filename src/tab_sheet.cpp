/*
 * tab_sheet.cpp
 *
 *  Created on: 2011-8-22
 *      Author: wuyangchun
 */
#include <QSpacerItem>
#include <QVBoxLayout>
#include "tab_sheet.h"
#include "send_thread.h"
#include <qmessagebox.h>

TabSheet::TabSheet(QWidget *parent) :
		QWidget(parent)
{
	m_sendThread = new SendThread(this);
}

TabSheet::~TabSheet()
{
	if (m_sendThread->isRunning())
	{
		m_sendThread->stop();
		m_sendThread->wait();
	}
	delete m_sendThread;
}

void TabSheet::setupUi(QHBoxLayout* layout)
{
	QHBoxLayout* simpleLayout = new QHBoxLayout();

	m_sendButton = new QPushButton(tr("send"));
	m_advancedButton = new QPushButton(tr("advance"));
	m_tipLabel = new QLabel();
	m_statusLabel1 = new QLabel();
	m_statusLabel2 = new QLabel();
	QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20,
			QSizePolicy::Expanding, QSizePolicy::Minimum);

	simpleLayout->addWidget(m_tipLabel);
	simpleLayout->addWidget(m_statusLabel1);
	simpleLayout->addWidget(m_statusLabel2);
	simpleLayout->addItem(horizontalSpacer);
	simpleLayout->addWidget(m_advancedButton);
	simpleLayout->addWidget(m_sendButton);

	m_advancedGroup = new QGroupBox(tr("advance:"));
//	m_advanceGroup->setStyleSheet("margin:5px 0px 0px 5px;padding:10px;border:3px solid red;border-radius:5px");
//	QString oldStyleSheet = m_advanceGroup->styleSheet();
	QHBoxLayout* advanceLayout = new QHBoxLayout(m_advancedGroup);
	advanceLayout->addWidget(new QLabel(tr("sendtype:")));
	m_sendTypeBox = new QComboBox();
	m_sendTypeBox->addItem(tr("total"), QVariant((int) E_TOTAL));
	m_sendTypeBox->addItem(tr("per second"), QVariant((int) E_SPEED));
	advanceLayout->addWidget(m_sendTypeBox);
	advanceLayout->addWidget(new QLabel(tr("count:")));
	m_countEdit = new QLineEdit();
	advanceLayout->addWidget(m_countEdit);
	advanceLayout->addItem(
			new QSpacerItem(40, 20, QSizePolicy::Expanding,
					QSizePolicy::Minimum));

	QVBoxLayout* vboxLayout = new QVBoxLayout();
	vboxLayout->addWidget(m_advancedGroup);
	vboxLayout->addLayout(simpleLayout);
	layout->addLayout(vboxLayout);
//	layout->addWidget(m_sendButton);
	m_advancedGroup->setVisible(false);
	m_bAdvanced = false;

	connect(m_sendButton, SIGNAL(released(void)), this, SLOT(onSend(void)));
//	connect(m_advanceButton, SIGNAL(toggled(bool)), m_advanceGroup, SLOT(setVisible(bool)));
	connect(m_advancedButton, SIGNAL(released(void)), this,
			SLOT(onAdvanced(void)));
	connect(m_sendThread, SIGNAL(finished(void)), this,
			SLOT(onSendFinish(void)));
	connect(m_sendThread, SIGNAL(counter(int, int)), this,
			SLOT(counter(int, int)));

	restoreSettings();
}

void TabSheet::showFailedTip(const QString& tip)
{
	showTip(QString("<font color=red>%1</font>").arg(tip));
}

void TabSheet::showSuccessfulTip(const QString& tip)
{
	showTip(QString("<font color=green>%1</font>").arg(tip));
}

void TabSheet::showTip(const QString& tip)
{
	if (m_tipLabel != NULL)
	{
		m_tipLabel->setText(tip);
	}
}

void TabSheet::onAdvanced()
{

	if (m_bAdvanced)
	{
		m_advancedGroup->setVisible(false);
		m_advancedButton->setText(tr("advance"));
		m_bAdvanced = !m_bAdvanced;
	}
	else
	{
		m_advancedGroup->setVisible(true);
		m_advancedButton->setText(tr("simple"));
		m_bAdvanced = !m_bAdvanced;
	}
}

void TabSheet::onSend()
{
	m_tipLabel->setText("");
	m_statusLabel1->setText("");
	m_statusLabel2->setText("");

	saveSettings();
	if (m_sendThread->isRunning()) //running
	{
		m_sendButton->setText(tr("send"));
		m_sendThread->stop();
		return;
	}

	//not running
	if (m_bAdvanced) //multi
	{
		int index = m_sendTypeBox->currentIndex();
		int count = m_countEdit->text().toInt();
//		QMessageBox::information(this, "test", QString("%1").arg(count));
		if (count == 0)
		{
			showFailedTip("please input a valid count");
			return;
		}
		m_sendButton->setText(tr("stop"));
		m_sendThread->start((SendType) m_sendTypeBox->itemData(index).toInt(),
				count);
	}
	else //singel
	{
		QString ret = sendData();
		if (!ret.isNull() && !ret.isEmpty())
		{
			showFailedTip(ret);
		}
		else
		{
			showSuccessfulTip(tr("Successful !"));
		}
	}
}

void TabSheet::onSendFinish()
{
	const QString& error = m_sendThread->getError();
	if (error.isEmpty()) //thread exit successful
	{
		showSuccessfulTip(tr("finished"));
	}
	else
	{
		showFailedTip(error);
	}

	m_sendButton->setText(tr("send"));

}

void TabSheet::counter(int count, int seconds)
{
	m_statusLabel1->setText(
			QString("total(time):%1(%2)").arg(count).arg(seconds));
	double speed = 0;
	if (seconds == 0)
	{
		speed = count;
	}
	else
	{
		speed = (double) count / seconds;
	}
	m_statusLabel2->setText(QString("speed:%1").arg(speed));
}
