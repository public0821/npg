/*
 * main_list_widget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */

#include "main_list_widget.h"
#include <qicon.h>
#include <qmessagebox.h>
#include "npg_define.h"
#include "protocol/protocol_factory.h"

MainListWidget::MainListWidget()
{
	// TODO Auto-generated constructor stub
//	setViewMode(QListView::IconMode);
//	setFlow(QListView::TopToBottom);
	QListWidgetItem* udp = new QListWidgetItem(
			QIcon(":/npg/protocol_udp"), K_UDP,
			this);
	QListWidgetItem* tcp = new QListWidgetItem(
			QIcon(":/npg/protocol_udp"), K_TCP,
			this);
	QListWidgetItem* icmp = new QListWidgetItem(
				QIcon(":/npg/protocol_udp"), K_ICMP,
				this);
	QListWidgetItem* arp = new QListWidgetItem(
					QIcon(":/npg/protocol_udp"), K_ARP,
					this);
	QListWidgetItem* dns = new QListWidgetItem(
						QIcon(":/npg/protocol_udp"), K_DNS,
						this);

	ProtocolFactory& protocol_factory = ProtocolFactory::instance();
	if (protocol_factory.isError())
	{
		QMessageBox::information(this, "tip", protocol_factory.errorStr());
	}	
	const std::vector<Protocol>& protocols = protocol_factory.protocols();
	std::vector<Protocol>::const_iterator it;
	for (it = protocols.begin(); it != protocols.end(); ++it)
	{
		QListWidgetItem* item = new QListWidgetItem(
			QIcon(QString::fromUtf8(it->icon().c_str())), it->name().c_str(),
			this);
		item->setTextAlignment(Qt::AlignLeft);
	}
	

	udp->setTextAlignment(Qt::AlignLeft);
	tcp->setTextAlignment(Qt::AlignLeft);
	icmp->setTextAlignment(Qt::AlignLeft);
	arp->setTextAlignment(Qt::AlignLeft);
	dns->setTextAlignment(Qt::AlignLeft);
}

MainListWidget::~MainListWidget()
{
	// TODO Auto-generated destructor stub
}

