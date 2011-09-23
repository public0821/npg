/*
 * main_tab_widget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: wuyangchun
 */

#include "main_tab_widget.h"
#include "public.h"
#include "udp_widget.h"
#include "tcp_widget.h"
#include "icmp_widget.h"
#include "arp_widget.h"

MainTabWidget::MainTabWidget()
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

	if (type == K_UDP)
	{
		sheet = new UdpWidget(this);
		index = QTabWidget::addTab(sheet,
				QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_UDP);
	}
	else if (type == K_TCP)
	{
		sheet = new TcpWidget(this);
		index = QTabWidget::addTab(sheet,
				QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_TCP);
	}
	else if (type == K_ICMP)
	{
		sheet = new IcmpWidget(this);
		index = QTabWidget::addTab(sheet,
				QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_ICMP);
	}
	else if (type == K_ARP)
		{
			sheet = new ArpWidget(this);
			index = QTabWidget::addTab(sheet,
					QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_ARP);
		}

	if (index != -1)
	{
		m_tabs.push_back(sheet);
		setCurrentIndex(index);
	}

	return index;
}
