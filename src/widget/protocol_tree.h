/*
 * protocol_tree.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef PROTOCOL_TREE_H
#define PROTOCOL_TREE_H

#include <QTreeWidget>
#include <qaction.h>
#include "protocol/protocol.h"
#include <QDropEvent>

enum EItemType
{
	E_ITEM_TYPE_CATEGORY = 1
	, E_ITEM_TYPE_FIELD = 2
	,	E_ITEM_TYPE_SUBFIELD = 2
};


class ProtocolTree: public QTreeWidget
{
Q_OBJECT

public:
	ProtocolTree(QWidget *parent);
	~ProtocolTree();
public:
	void setup(Protocol protocol);
//protected:
//	void mousePressEvent(QMouseEvent *event);
//	void mouseMoveEvent(QMouseEvent *event);
//	void performDrag();
//	void dragMoveEvent(QDragMoveEvent *event);
//	void dragEnterEvent(QDragEnterEvent *event);
	//void dropEvent(QDropEvent *event);
private slots:
	void onShowPopup(const QPoint &pos);
	void onDelete();
	void onAdd();
	void itemWidgetTextChange(QTreeWidgetItem *, int);
	void onAddField();
private:
	QTreeWidgetItem* getSelectedItem();
	QTreeWidgetItem* addFieldItem(QTreeWidgetItem* parent, QTreeWidgetItem * preceding, const Field& field);
	QTreeWidgetItem* addSubFieldItem(QTreeWidgetItem* parent, const Field& field);
	QTreeWidgetItem * addCategoryItem(QTreeWidget * parent, QTreeWidgetItem * preceding, const Category& category);
private:
	QAction* m_delete_action;
	QAction* m_add_action;
	QAction* m_add_field_action;
	Protocol m_protocol;
	//std::map<sstring, int>  m_multi_category_count;
	//QPoint m_start_pos;
};

#endif // PROTOCOL_TREE_H
