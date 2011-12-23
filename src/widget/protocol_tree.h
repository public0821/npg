#ifndef PROTOCOL_TREE_H
#define PROTOCOL_TREE_H

#include <QTreeWidget>
#include <qaction.h>
#include "protocol/protocol.h"

enum EItemType
{
	E_ITEM_TYPE_CATEGORY = 1, E_ITEM_TYPE_FIELD = 2,
};


class ProtocolTree: public QTreeWidget
{
Q_OBJECT

public:
	ProtocolTree(QWidget *parent);
	~ProtocolTree();
public:
	void setup(Protocol protocol);
private slots:
	void onShowPopup(const QPoint &pos);
	void onDelete();
	void onAdd();
	void itemWidgetTextChange(QTreeWidgetItem *, int);
	void onAddField();
private:
	QTreeWidgetItem* getSelectedItem();
	QTreeWidgetItem* addFieldItem(QTreeWidgetItem* parent, QTreeWidgetItem * preceding, const Field& field);

	QTreeWidgetItem * addCategoryItem(QTreeWidget * parent, QTreeWidgetItem * preceding, const Category& category);
private:
	QAction* m_delete_action;
	QAction* m_add_action;
	QAction* m_add_field_action;
	Protocol m_protocol;
	std::map<sstring, int>  m_multi_category_count;
};

#endif // PROTOCOL_TREE_H
