/*
 * main_tab_widget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */

#include "main_tab_widget.h"
#include "npg_define.h"
#include "data_tab_sheet.h"
#include "tcp_widget.h"
#include "protocol/protocol_factory.h"
#include "protocol_tab_sheet.h"

MainTabWidget::MainTabWidget(const QMap<QString, QString>& name_icons,  QWidget* parent)
:QTabWidget(parent), m_name_icons(name_icons)
{
	setTabsClosable(true);
	setMovable(true);

	connect(this, SIGNAL(tabCloseRequested (int)), this,
			SLOT(onCloseTab (int)));
}

MainTabWidget::~MainTabWidget()
{
}

void MainTabWidget::onCloseTab(int index)
{
	removeTab(index);
	delete m_tabs[index];
	m_tabs.remove(index);
}

int MainTabWidget::addTab(const QString &type)
{
	int index = -1;
	TabSheet* sheet = NULL;

	if (type == K_PROTOCOL_UDP)
	{
		sheet = new DataTabSheet(K_PROTOCOL_UDP, this);
	}
	else if (type == K_PROTOCOL_TCP)
	{
		sheet = new DataTabSheet(K_PROTOCOL_TCP, this);
	}
//	else if (type == K_PROTOCOL_ICMP)
//	{
//		sheet = new IcmpWidget(type, this);
//	}
	//else if (type == K_PROTOCOL_ARP)
	//{
	//	sheet = new ArpWidget(type, this);
	//}
	//else if (type == K_PROTOCOL_DNS)
	//{
	//	sheet = new DnsWidget(type, this);
	//}
	else
	{
		Protocol protocol = ProtocolFactory::instance().protocol(type);
		if (!protocol.empty())
		{
			sheet = new ProtocolTabSheet(protocol, this);
			index = QTabWidget::addTab(sheet,
				QIcon(protocol.icon()), type);
		}
		
	}

	QMap<QString, QString>::const_iterator it = m_name_icons.find(type);
	if (it != m_name_icons.end())
	{
		index = QTabWidget::addTab(sheet,
			QIcon(it.value()), it.key());
	}
	
	if (index != -1)
	{
		m_tabs.push_back(sheet);
		setCurrentIndex(index);
	}

	return index;
}
