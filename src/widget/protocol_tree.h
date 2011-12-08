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
private:
	QTreeWidgetItem* getSelectedItem();
		QTreeWidgetItem* addChildItem(QTreeWidgetItem* parent,
			EItemType item_type, const QString& name, const QString& text, const QString& tip);

		QTreeWidgetItem* addTopLevelItem(EItemType item_type, const QString& name, const QString& text, const QString& tip);

	QWidget* getFieldWidget(const Field& field);
	void addCategoryItem(const Category& category);
private:
	QAction* m_delete_action;
	QAction* m_add_action;
	Protocol m_protocol;
};

#endif // PROTOCOL_TREE_H
