#include "protocol_tree_item.h"

ProtocolTreeItem::ProtocolTreeItem(QWidget * widget, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.layout->addWidget(widget, 0, 0);
	
}

ProtocolTreeItem::~ProtocolTreeItem()
{

}
