#include "protocol_tree.h"
#include <qmessagebox.h>
#include <qmenu.h>
#include <qlineedit.h>
#include <qlabel.h>

enum EItemType
{
	E_ITEM_TYPE_CATEGORY = 1, E_ITEM_TYPE_FIELD = 2,
};

ProtocolTree::ProtocolTree(QWidget *parent) :
		QTreeWidget(parent)
{

}

ProtocolTree::~ProtocolTree()
{

}

void ProtocolTree::setup(Protocol protocol)
{
	setColumnCount(3);
	QStringList head_list;
	head_list << "field" << "value" << "tip";
	setHeaderLabels(head_list);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this,
			SLOT(onShowPopup(const QPoint &)));
	setContextMenuPolicy(Qt::CustomContextMenu);
	setDragDropMode(NoDragDrop);

	m_delete_action = new QAction(tr("delete"), this);
	m_add_action = new QAction(tr("add"), this);

	connect(m_delete_action, SIGNAL(triggered()), this, SLOT(onDelete()));
	connect(m_add_action, SIGNAL(triggered()), this, SLOT(onAdd()));

	QStringList protocol_text;
	protocol_text << protocol.name().c_str();
	QTreeWidgetItem *protocol_item = new QTreeWidgetItem(this, protocol_text);
	std::vector<Category>& categorys = protocol.Categorys();
	std::vector<Category>::iterator it_category;
	for (it_category = categorys.begin(); it_category != categorys.end();
			++it_category)
	{
		QTreeWidgetItem *catetory_item = addChildItem(protocol_item,
				it_category->text().c_str(), it_category->tip().c_str());

		std::vector<Field>& fields = it_category->fields();
		std::vector<Field>::iterator it_field;
		for (it_field = fields.begin(); it_field != fields.end(); ++it_field)
		{
			QTreeWidgetItem *field_item = addChildItem(catetory_item,
					it_field->text().c_str(), it_field->tip().c_str());
			QWidget* widget = getFieldWidget(*it_field);
			setItemWidget(field_item, 1, widget);
		}
	}

	expandAll();
	resizeColumnToContents(0);
	resizeColumnToContents(2);
}

void ProtocolTree::onShowPopup(const QPoint &pos)
{
	QTreeWidgetItem * item = itemAt(pos);

	if (item != NULL)
	{
		if (item->data(0, Qt::UserRole).toInt() == (int) E_ITEM_TYPE_CATEGORY)
		{
			QMenu menu(this);

			menu.addAction(m_delete_action);
			menu.addAction(m_add_action);

			m_add_action->setDisabled(true);
			m_delete_action->setDisabled(true);
			m_add_action->setDisabled(true);
			m_delete_action->setDisabled(true);

			menu.exec(mapToGlobal(pos));
		}
	}
}

void ProtocolTree::onAdd()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL)
	{
		return;
	}
}

void ProtocolTree::onDelete()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL)
	{
		return;
	}

	delete item;
}

QTreeWidgetItem* ProtocolTree::getSelectedItem()
{
	QList<QTreeWidgetItem*> items = selectedItems();
	if (items.count() == 0)
	{
		QMessageBox::information(this, tr("tip"), tr("please select a node"));
		return NULL;
	}
	if (items.count() > 1)
	{
		QMessageBox::information(this, tr("tip"),
				tr("only can select one node"));
		return NULL;
	}

	return items.at(0);
}

QTreeWidgetItem* ProtocolTree::addChildItem(QTreeWidgetItem* parent,
		const QString& name, const QString& tip)
{
	QStringList text_list;
	text_list << name << "" << tip;
	QTreeWidgetItem *leaf = new QTreeWidgetItem(parent, text_list);

	return leaf;
}

QWidget* ProtocolTree::getFieldWidget(const Field& field)
{
	QWidget* widget = NULL;

	switch (field.inputMethod())
	{
	case E_FIELD_INPUT_METHOD_EDIT:
		widget = new QLineEdit(field.defaultValue().c_str());
		break;
	case E_FIELD_INPUT_METHOD_SELECT:
		widget = new QLineEdit(field.defaultValue().c_str());
		break;
	case E_FIELD_INPUT_METHOD_NONE:
	default:
		QLabel* label = new QLabel(field.defaultValue().c_str());
		label->setAlignment(Qt::AlignCenter);
		widget = label;
		break;
	}

	return widget;
}
