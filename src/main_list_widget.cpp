/*
 * TypeListWidget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: wuyangchun
 */

#include "main_list_widget.h"
#include <qicon.h>
#include "public.h"

MainListWidget::MainListWidget()
{
	// TODO Auto-generated constructor stub
//	setViewMode(QListView::IconMode);
//	setFlow(QListView::TopToBottom);
	QListWidgetItem* udp = new QListWidgetItem(
			QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_UDP,
			this);
	QListWidgetItem* tcp = new QListWidgetItem(
			QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_TCP,
			this);
	QListWidgetItem* icmp = new QListWidgetItem(
				QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_ICMP,
				this);
	QListWidgetItem* arp = new QListWidgetItem(
					QIcon(QString::fromUtf8(":/npg/resource/udp.png")), K_ARP,
					this);
	udp->setTextAlignment(Qt::AlignLeft);
	tcp->setTextAlignment(Qt::AlignLeft);
	icmp->setTextAlignment(Qt::AlignLeft);
	arp->setTextAlignment(Qt::AlignLeft);
}

MainListWidget::~MainListWidget()
{
	// TODO Auto-generated destructor stub
}

