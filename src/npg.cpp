/*
 * npg.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */
#include "npg.h"

#include <qstringlist.h>
#include <qsettings.h>
#include "widget/npg_define.h"
#include <qmessagebox.h>

npg::npg(QWidget *parent) :
		QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.action_quit, SIGNAL(triggered(bool)), this, SLOT(close ()));
	ui.toolBar->addAction(ui.action_quit);

	m_main_splitter = new QSplitter(Qt::Horizontal);

	m_type_list = new MainListWidget();
	m_tab_widget = new MainTabWidget();

	m_main_splitter->addWidget(m_type_list);
	m_main_splitter->addWidget(m_tab_widget);
	m_main_splitter->setStretchFactor(1, 1);

	setCentralWidget(m_main_splitter);

	connect(m_type_list, SIGNAL(itemDoubleClicked(QListWidgetItem* )), this,
			SLOT(itemDoubleClicked(QListWidgetItem* )));

	restoreSettings();
	//m_main_splitter->setGeometry (100,100,400,300 );
	//resize(400, 300);
//	/setsi
//	m_tabWidget->addTab(new UdpWidget(m_tabWidget), "udp");
}

npg::~npg()
{

}

void npg::itemDoubleClicked(QListWidgetItem * item)
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

