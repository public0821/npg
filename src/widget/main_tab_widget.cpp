/*
 * main_tab_widget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */

#include "main_tab_widget.h"
#include "npg_define.h"
#include "udp_widget.h"
#include "tcp_widget.h"
#include "icmp_widget.h"
#include "arp_widget.h"
#include "dns_widget.h"
#include "protocol/protocol_factory.h"
#include "protocol_widget.h"

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
	// TODO Auto-generated destructor stub
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

	if (type == "UDP")
	{
		sheet = new UdpWidget(type, this);
	}
	else if (type == "TCP")
	{
		sheet = new TcpWidget(type, this);
	}
	else if (type == "ICMP")
	{
		sheet = new IcmpWidget(type, this);
	}
	else if (type == "ARP")
	{
		sheet = new ArpWidget(type, this);
	}
	else if (type == "DNS")
	{
		sheet = new DnsWidget(type, this);
	}
	else
	{
		Protocol protocol = ProtocolFactory::instance().protocol(type.toStdString());
		if (!protocol.empty())
		{
			sheet = new ProtocolWidget(protocol, this);
			index = QTabWidget::addTab(sheet,
				QIcon(QString::fromUtf8(protocol.icon().c_str())), type);
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