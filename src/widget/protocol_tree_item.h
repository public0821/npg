#ifndef PROTOCOL_TREE_ITEM_H
#define PROTOCOL_TREE_ITEM_H

#include <QWidget>
#include "ui_protocol_tree_item.h"

class ProtocolTreeItem : public QWidget
{
	Q_OBJECT

public:
	ProtocolTreeItem(QWidget * widget, QWidget *parent = 0);
	~ProtocolTreeItem();

private:
	Ui::ProtocolTreeItem ui;
};

#endif // PROTOCOL_TREE_ITEM_H
