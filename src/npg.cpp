/*
 * npg.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */
#include "npg.h"

#include <qstringlist.h>
#include <qsettings.h>
#include "npg_define.h"
#include <qmessagebox.h>

npg::npg(QWidget *parent) :
		QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.action_quit, SIGNAL(triggered(bool)), this, SLOT(close()));
	ui.toolBar->addAction(ui.action_quit);

	m_main_splitter = new QSplitter(Qt::Horizontal);

	QMap<QString, QString> name_icons;
	name_icons.insert(K_PROTOCOL_UDP, ":/npg/protocol_default");
	name_icons.insert(K_PROTOCOL_TCP, ":/npg/protocol_default");
	//name_icons.insert(K_PROTOCOL_ICMP, ":/npg/protocol_default");
	//name_icons.insert(K_PROTOCOL_ARP, ":/npg/protocol_default");
	//name_icons.insert(K_PROTOCOL_DNS, ":/npg/protocol_default");

	m_type_list = new MainListWidget(name_icons);
	m_tab_widget = new MainTabWidget(name_icons);

	m_main_splitter->addWidget(m_type_list);
	m_main_splitter->addWidget(m_tab_widget);
	m_main_splitter->setStretchFactor(1, 1);

	setCentralWidget(m_main_splitter);

	connect(m_type_list, SIGNAL(itemDoubleClicked(QListWidgetItem* )), this,
			SLOT(onItemDoubleClicked(QListWidgetItem* )));

	restoreSettings();
	//m_main_splitter->setGeometry (100,100,400,300 );
	//resize(400, 300);
//	/setsi
//	m_tabWidget->addTab(new UdpWidget(m_tabWidget), "udp");
}

npg::~npg()
{

}

void npg::onItemDoubleClicked(QListWidgetItem * item)
{
	if (item == NULL)
	{
		return;
	}

	QString data_type = item->text();
	m_tab_widget->addTab(data_type);

}

void npg::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);

	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("mainSplitter", m_main_splitter->saveState());
	settings.endGroup();
}

void npg::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);

	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	m_main_splitter->restoreState(settings.value("mainSplitter").toByteArray());
	settings.endGroup();
}

void npg::closeEvent(QCloseEvent *event)
 {
	saveSettings();
    QWidget::closeEvent(event);
 }

