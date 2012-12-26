/*
 * npg.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */
#include "npg.h"

#include <qstringlist.h>
#include <qsettings.h>
#include "config.h"
#include <qmessagebox.h>
#include "widget/converter_dialog.h"
#include "widget/about_dialog.h"
#include "logger.h"
#include "qresource.h"
#include "protocol/protocol_factory.h"


const static char K_INTERNAL_PROTOCOL_UDP[] = "UDP";
const static char K_INTERNAL_PROTOCOL_TCP[] = "TCP";

Npg::Npg(QWidget *parent) :
		QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.action_quit, SIGNAL(triggered(bool)), this, SLOT(close()));
	connect(ui.action_about, SIGNAL(triggered(bool)), this, SLOT(onAbout()));

	ui.action_new->setIcon(QIcon(ICON_CATEGORY_ADD));
	ui.action_quit->setIcon(QIcon(ICON_QUIT));
	ui.action_tool_ip->setIcon(QIcon(ICON_FIELD_IP));
	ui.action_tool_hex->setIcon(QIcon(ICON_FIELD_HEX));
	ui.action_tool_time->setIcon(QIcon(ICON_FIELD_TIME));
	ui.action_tool_base64->setIcon(QIcon(ICON_FIELD_BASE64));
	ui.action_about->setIcon(QIcon(ICON_ABOUT));

	ui.action_tool_ip->setData((int) E_CONVERTER_IP);
	ui.action_tool_hex->setData((int) E_CONVERTER_HEX);
	ui.action_tool_time->setData((int) E_CONVERTER_TIME);
	ui.action_tool_base64->setData((int) E_CONVERTER_BASE64);

	ui.action_new->setIconVisibleInMenu(true);
	ui.action_quit->setIconVisibleInMenu(true);
	ui.action_tool_ip->setIconVisibleInMenu(true);
	ui.action_tool_hex->setIconVisibleInMenu(true);
	ui.action_tool_time->setIconVisibleInMenu(true);
	ui.action_tool_base64->setIconVisibleInMenu(true);
	ui.action_about->setIconVisibleInMenu(true);

	connect(ui.action_tool_ip, SIGNAL(triggered(bool)), this, SLOT(onConverterClicked()));
	connect(ui.action_tool_hex, SIGNAL(triggered(bool)), this, SLOT(onConverterClicked()));
	connect(ui.action_tool_time, SIGNAL(triggered(bool)), this, SLOT(onConverterClicked()));
	connect(ui.action_tool_base64, SIGNAL(triggered(bool)), this, SLOT(onConverterClicked()));

	ui.toolBar->addAction(ui.action_new);
	ui.toolBar->addAction(ui.action_quit);
	ui.toolBar->addAction(ui.action_tool_ip);
	ui.toolBar->addAction(ui.action_tool_hex);
	ui.toolBar->addAction(ui.action_tool_time);
	ui.toolBar->addAction(ui.action_tool_base64);
	ui.toolBar->addAction(ui.action_about);

	m_main_splitter = new QSplitter(Qt::Horizontal);
	m_log_splitter = new QSplitter(Qt::Vertical);

	QMap<QString, QString> internal_protocol;
	internal_protocol.insert(K_INTERNAL_PROTOCOL_UDP, ICON_PROTOCOL_DEFAULT);
	internal_protocol.insert(K_INTERNAL_PROTOCOL_TCP, ICON_PROTOCOL_DEFAULT);
	m_logger = new QTextBrowser(this);
	Logger::instance().bind(m_logger);

	bool ret = ProtocolFactory::instance().loadXml();
	if (!ret) {
		QMessageBox::information(this, tr("tip"), tr("load config failed"));
	}

	m_type_list = new MainListWidget(internal_protocol);
	m_tab_widget = new MainTabWidget(internal_protocol);

	m_log_splitter->addWidget(m_tab_widget);
	m_log_splitter->addWidget(m_logger);
	m_main_splitter->addWidget(m_type_list);
	m_main_splitter->addWidget(m_log_splitter);
	m_log_splitter->setStretchFactor(0, 1);
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

Npg::~Npg() {

}

void Npg::onItemDoubleClicked(QListWidgetItem * item) {
	if (item == NULL) {
		return;
	}

	QString data_type = item->text();
	m_tab_widget->addTab(data_type);

}

void Npg::saveSettings() {
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);

	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("logSplitter", m_log_splitter->saveState());
	settings.setValue("mainSplitter", m_main_splitter->saveState());
	settings.endGroup();
}

void Npg::restoreSettings() {
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);

	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	m_main_splitter->restoreState(settings.value("mainSplitter").toByteArray());
	m_log_splitter->restoreState(settings.value("logSplitter").toByteArray());
	settings.endGroup();
}

void Npg::closeEvent(QCloseEvent *event) {
	saveSettings();
	QWidget::closeEvent(event);
}

void Npg::onConverterClicked() {
	QAction* action = qobject_cast<QAction*>(sender());
	EConverterType type = (EConverterType) action->data().toInt();

	ConverterDialog dialog(type, action->icon());

	dialog.exec();
}

void Npg::onAbout() {
	AboutDialog dialog(this);
	dialog.exec();
}
