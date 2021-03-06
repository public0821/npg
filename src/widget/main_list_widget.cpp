/*
 * main_list_widget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */

#include "main_list_widget.h"
#include <qicon.h>
#include <qmessagebox.h>
#include "config.h"
#include "protocol/protocol_factory.h"

MainListWidget::MainListWidget(const QMap<QString, QString>& internal_protocol, QWidget* parent)
:
		QListWidget(parent)
{
	setIconSize(QSize(64, 64));
//	setViewMode(QListView::IconMode);
//	setFlow(QListView::TopToBottom);
	QMap<QString, QString>::const_iterator it_name_icon;
	for (it_name_icon = internal_protocol.begin(); it_name_icon != internal_protocol.end(); ++it_name_icon) {
		QListWidgetItem* item = new QListWidgetItem(QIcon(it_name_icon.value()), it_name_icon.key(), this);
		item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	}
	ProtocolFactory& protocol_factory = ProtocolFactory::instance();
	const std::vector<Protocol>& protocols = protocol_factory.protocols();
	std::vector<Protocol>::const_iterator it_protocol;
	for (it_protocol = protocols.begin(); it_protocol != protocols.end(); ++it_protocol) {
		if (it_protocol->needShow()) {
			QListWidgetItem* item = new QListWidgetItem(
					QIcon(it_protocol->icon()), it_protocol->name(),
					this);
			item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
		}
	}

}

MainListWidget::~MainListWidget()
{
}

