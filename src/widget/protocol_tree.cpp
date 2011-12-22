#include "protocol_tree.h"
#include <qmessagebox.h>
#include <qmenu.h>
#include "protocol_tree_item.h"
#include <QCheckBox>

ProtocolTree::ProtocolTree(QWidget *parent) :
		QTreeWidget(parent)
{

}

ProtocolTree::~ProtocolTree()
{

}

void ProtocolTree::setup(Protocol protocol)
{
	m_protocol = protocol;
	setColumnCount(6);
	QStringList head_list;
	head_list << "field" << "value"<<"" <<"type"<<"length"<< "tip";
	setHeaderLabels(head_list);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this,
			SLOT(onShowPopup(const QPoint &)));
	setContextMenuPolicy(Qt::CustomContextMenu);
	setDragDropMode(NoDragDrop);

	m_delete_action = new QAction(QIcon(":/npg/category_delete"), tr("Delete(&A)"), this);
	m_delete_action->setShortcut(QKeySequence::fromString("Ctrl+D"));
	m_add_action = new QAction(QIcon(":/npg/category_add"), tr("add(&A)"), this);
	m_add_action->setShortcut(QKeySequence::fromString("Ctrl+A"));
	m_delete_action->setIconVisibleInMenu(true);
	m_add_action->setIconVisibleInMenu(true);

	connect(m_delete_action, SIGNAL(triggered()), this, SLOT(onDelete()));
	connect(m_add_action, SIGNAL(triggered()), this, SLOT(onAdd()));

	const std::vector<Category>& categorys = protocol.categorys();
	std::vector<Category>::const_iterator it_category;
	for (it_category = categorys.begin(); it_category != categorys.end();
			++it_category)
	{
		addCategoryItem(*it_category);
	}

	expandAll();
	resizeColumnToContents(0);
	resizeColumnToContents(1);
	resizeColumnToContents(2);
	resizeColumnToContents(3);
	resizeColumnToContents(4);
	resizeColumnToContents(5);

	//viewport()->setBackgroundRole(QPalette::Background);
	//ssetAutoFillBackground(false);
}

void ProtocolTree::onShowPopup(const QPoint &pos)
{
	QTreeWidgetItem * item = itemAt(pos);

	if (item != NULL)
	{
		EItemType item_type = (EItemType)item->data(0, Qt::UserRole).toInt();
		if (item_type ==  E_ITEM_TYPE_CATEGORY)
		{
			sstring name = item->data(1, Qt::UserRole).toString().toStdString();
			Category category = m_protocol.category(name);
			if (category.isMany())
			{
				QMenu menu(this);

				menu.addAction(m_add_action);
				m_add_action->setEnabled(true);

				std::map<sstring, int>::iterator it;
				it = m_multi_category_count.find(category.name());
				if (it != m_multi_category_count.end() && it->second > 1)
				{
					menu.addAction(m_delete_action);
					m_delete_action->setEnabled(true);
				}

				menu.exec(mapToGlobal(pos));
			}	
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

	EItemType item_type = (EItemType)item->data(0, Qt::UserRole).toInt();
	if (item_type !=  E_ITEM_TYPE_CATEGORY)
	{
		return;
	}

	sstring name = item->data(1, Qt::UserRole).toString().toStdString();
	Category category = m_protocol.category(name);
	addCategoryItem(category);
}

void ProtocolTree::onDelete()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL)
	{
		return;
	}


	EItemType item_type = (EItemType)item->data(0, Qt::UserRole).toInt();
	if (item_type !=  E_ITEM_TYPE_CATEGORY)
	{
		return;
	}

	sstring name = item->data(1, Qt::UserRole).toString().toStdString();
	std::map<sstring, int>::iterator it;
	it = m_multi_category_count.find(name);
	if (it != m_multi_category_count.end())
	{
		--it->second;
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

QTreeWidgetItem* ProtocolTree::addFieldItem(QTreeWidgetItem* parent, const Field& field)
{
	QStringList text_list;
	text_list << field.text().c_str() << ""<<""<<field.typeString().c_str()<< QString("%1").arg(field.length())<< field.tip().c_str();
	QTreeWidgetItem *item = new QTreeWidgetItem(parent, text_list);
	item->setData(0, Qt::UserRole, QVariant(E_ITEM_TYPE_FIELD));
	item->setData(1, Qt::UserRole, QVariant(field.name().c_str()));
	item->setTextAlignment(3, Qt::AlignHCenter|Qt::AlignVCenter);

	ProtocolTreeItem* tree_item = new ProtocolTreeItem(item, field);
	if (field.type() == E_FIELD_TYPE_STRING)
	{
		connect(tree_item, SIGNAL(textChange(QTreeWidgetItem *, int)), this, SLOT(itemWidgetTextChange(QTreeWidgetItem *, int)));
	}
	setItemWidget(item, 1, tree_item);

	if (field.defaultValue() == K_DEFAULT_VALUE_DEFAULT)
	{
		QCheckBox* checkbox = new QCheckBox(this);
		setItemWidget(item, 2, checkbox);
		connect(checkbox, SIGNAL(stateChanged (int)), tree_item, SLOT(checkBoxStateChange(int)));
		tree_item->setEnabled(false);
	}

	item->setIcon(0, QIcon(field.icon().c_str()));

	return item;
}



void ProtocolTree::addCategoryItem(const Category& category)
{
	QStringList text_list;
	text_list << category.text().c_str()<<""<<""<<""<<category.tip().c_str();
	QTreeWidgetItem *category_item = new QTreeWidgetItem(this, text_list);
	category_item->setData(0, Qt::UserRole, QVariant(E_ITEM_TYPE_CATEGORY));
	category_item->setData(1, Qt::UserRole, QVariant(category.name().c_str()));
	category_item->setIcon(0, QIcon(":/npg/category"));

	const std::vector<Field>& fields = category.fields();
	std::vector<Field>::const_iterator it_field;
	for (it_field = fields.begin(); it_field != fields.end(); ++it_field)
	{
		addFieldItem(category_item, *it_field);
	}

	if (category.isMany())
	{
		std::map<sstring, int>::iterator it;
		it = m_multi_category_count.find(category.name());
		if (it != m_multi_category_count.end())
		{
			++it->second;
		}
		else
		{
			m_multi_category_count.insert(std::make_pair(category.name(),1));
		}
	}
}

void ProtocolTree::itemWidgetTextChange(QTreeWidgetItem *item , int count)
{
	item->setText(4, QString("%1").arg(count));
}
