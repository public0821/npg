#include "protocol_tree.h"
#include <qmessagebox.h>
#include <qmenu.h>
#include <qlineedit.h>
#include <qlabel.h>

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
	setColumnCount(3);
	QStringList head_list;
	head_list << "field" << "value" << "tip";
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

				menu.addAction(m_delete_action);
				menu.addAction(m_add_action);

				m_add_action->setEnabled(true);
				m_delete_action->setEnabled(true);

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
		EItemType item_type, const QString& name, const QString& text, const QString& tip)
{
	QStringList text_list;
	text_list << text << "" << tip;
	QTreeWidgetItem *item = new QTreeWidgetItem(parent, text_list);
	item->setData(0, Qt::UserRole, QVariant(item_type));
	item->setData(1, Qt::UserRole, QVariant(name));

	return item;
}

QTreeWidgetItem* ProtocolTree::addTopLevelItem(EItemType item_type, const QString& name, const QString& text, const QString& tip)
{
	QStringList text_list;
	text_list << text << "" << tip;
	QTreeWidgetItem *item = new QTreeWidgetItem(this, text_list);
	item->setData(0, Qt::UserRole, QVariant(item_type));
	item->setData(1, Qt::UserRole, QVariant(name));

	return item;
}

QWidget* ProtocolTree::getFieldWidget(const Field& field)
{
	QWidget* widget = NULL;

	if (field.inputMethod() == E_FIELD_INPUT_METHOD_EDIT)
	{
		QLineEdit* edit = new QLineEdit(field.defaultValue().c_str());
		switch (field.type())
		{
		case E_FIELD_TYPE_INT:	
			edit->setValidator(new QIntValidator(field.minValue(), field.maxValue(), this));	
//			edit->setLineWidth(10);
			break;
		case E_FIELD_TYPE_IP:
			edit->setInputMask("000.000.000.000");
			break;
		default:
			break;
		}
		widget = edit;
	}
	else if(field.inputMethod() == E_FIELD_INPUT_METHOD_SELECT) 
	{
		widget = new QLineEdit(field.defaultValue().c_str());
	}
	else
	{
		QLabel* label = new QLabel(field.defaultValue().c_str());
		label->setAlignment(Qt::AlignCenter);
		widget = label;
	}

	return widget;
}


void ProtocolTree::addCategoryItem(const Category& category)
{
	QTreeWidgetItem *category_item = addTopLevelItem(E_ITEM_TYPE_CATEGORY,category.name().c_str(),
		category.text().c_str(), category.tip().c_str());
	QBrush brush(QColor(125,0,125));
	category_item->setBackground(0, brush);
	category_item->setBackground(1, brush);
	category_item->setBackground(2, brush);
	const std::vector<Field>& fields = category.fields();
	std::vector<Field>::const_iterator it_field;
	for (it_field = fields.begin(); it_field != fields.end(); ++it_field)
	{
		QTreeWidgetItem *field_item = addChildItem(category_item, E_ITEM_TYPE_FIELD,category.name().c_str(),
			it_field->text().c_str(), it_field->tip().c_str());
		QWidget* widget = getFieldWidget(*it_field);
		setItemWidget(field_item, 1, widget);
	}
}
