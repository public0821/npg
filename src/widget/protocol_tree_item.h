#ifndef PROTOCOL_TREE_ITEM_H
#define PROTOCOL_TREE_ITEM_H

#include <QWidget>
#include "ui_protocol_tree_item.h"
#include "protocol/field.h"
#include <QTreeWidgetItem>

class ProtocolTreeItem : public QWidget
{
	Q_OBJECT

public:
	ProtocolTreeItem(QTreeWidgetItem *item, const Field& field, QWidget *parent = 0);
	~ProtocolTreeItem();
	QString value();
private:
	QWidget* getFieldWidget(const Field& field);
public:
signals:
	void textChange(QTreeWidgetItem *, int);
protected slots:
	void onTextChange();
private:
	Ui::ProtocolTreeItem ui;
	Field m_field;
	QWidget* m_child;
	QTreeWidgetItem * m_item;
};

#endif // PROTOCOL_TREE_ITEM_H
