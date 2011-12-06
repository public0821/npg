#ifndef PROTOCOL_TREE_H
#define PROTOCOL_TREE_H

#include <QTreeWidget>
#include <qaction.h>
#include "protocol/protocol.h"

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
	QTreeWidgetItem* addChildItem(QTreeWidgetItem* parent, const QString& name,
			const QString& tip);
	QWidget* getFieldWidget(const Field& field);
private:
	QAction* m_delete_action;
	QAction* m_add_action;
};

#endif // PROTOCOL_TREE_H
