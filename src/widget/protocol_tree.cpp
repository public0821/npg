#include "protocol_tree.h"
#include <qmessagebox.h>
#include <qmenu.h>
#include "protocol_tree_item.h"
#include <QCheckBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include "field_select_dialog.h"

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
	head_list << "field" << "value" << "" << "type" << "length" << "tip";
	setHeaderLabels(head_list);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this,
			SLOT(onShowPopup(const QPoint &)));
	setContextMenuPolicy(Qt::CustomContextMenu);
	//setDragDropMode(NoDragDrop);
	setDragDropMode(InternalMove);

	m_delete_action = new QAction(QIcon(":/npg/category_delete"),
			tr("Delete(&A)"), this);
	m_delete_action->setShortcut(QKeySequence::fromString("Ctrl+D"));
	m_add_action = new QAction(QIcon(":/npg/category_add"), tr("Add(&A)"),
			this);
	m_add_action->setShortcut(QKeySequence::fromString("Ctrl+A"));
	m_add_field_action = new QAction(QIcon(":/npg/category_add"),
			tr("Add Field(&A)"), this);
	m_delete_action->setIconVisibleInMenu(true);
	m_add_action->setIconVisibleInMenu(true);
	m_add_field_action->setIconVisibleInMenu(true);

	connect(m_delete_action, SIGNAL(triggered()), this, SLOT(onDelete()));
	connect(m_add_action, SIGNAL(triggered()), this, SLOT(onAdd()));
	connect(m_add_field_action, SIGNAL(triggered()), this, SLOT(onAddField()));

	const std::vector<Category>& categorys = protocol.categorys();
	std::vector<Category>::const_iterator it_category;
	QTreeWidgetItem *preceding = NULL;
	for (it_category = categorys.begin(); it_category != categorys.end();
			++it_category)
	{
		preceding = addCategoryItem(this, preceding, *it_category);
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
		EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
		if (item_type == E_ITEM_TYPE_CATEGORY)
		{
			sstring name = item->data(1, Qt::UserRole).toString().toStdString();
			Category category = m_protocol.category(name);

			QMenu menu(this);
			if (category.isMany())
			{
				menu.addAction(m_add_action);
				m_add_action->setEnabled(true);

				std::map<sstring, int>::iterator it;
				it = m_multi_category_count.find(category.name());
				if (it != m_multi_category_count.end() && it->second > 1)
				{
					menu.addAction(m_delete_action);
					m_delete_action->setEnabled(true);
				}
			}
			if (category.optionalFieldCount() > 0)
			{
				menu.addAction(m_add_field_action);
				m_add_field_action->setEnabled(true);
			}
			if (!menu.isEmpty())
			{
				menu.exec(mapToGlobal(pos));
			}

		}
		else if (item_type == E_ITEM_TYPE_FIELD)
		{
			sstring category_name =
					item->parent()->data(1, Qt::UserRole).toString().toStdString();
			sstring field_name =
					item->data(1, Qt::UserRole).toString().toStdString();
			Category category = m_protocol.category(category_name);
			Field field = category.field(field_name);
			if (field.isOptional())
			{
				QMenu menu(this);

				menu.addAction(m_add_action);
				m_add_action->setEnabled(true);

				menu.addAction(m_delete_action);
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

	EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
	if (item_type == E_ITEM_TYPE_CATEGORY)
	{
		sstring name = item->data(1, Qt::UserRole).toString().toStdString();
		Category category = m_protocol.category(name);
		addCategoryItem(this, item, category);
	}
	else if (item_type == E_ITEM_TYPE_FIELD)
	{
		sstring category_name =
				item->parent()->data(1, Qt::UserRole).toString().toStdString();
		sstring field_name =
				item->data(1, Qt::UserRole).toString().toStdString();
		Category category = m_protocol.category(category_name);
		Field field = category.field(field_name);
		addFieldItem(item->parent(), item, field);
	}
}

void ProtocolTree::onAddField()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL)
	{
		return;
	}

	EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
	if (item_type == E_ITEM_TYPE_CATEGORY)
	{
		sstring name = item->data(1, Qt::UserRole).toString().toStdString();
		Category category = m_protocol.category(name);
		std::vector<Field> optional_fields = category.optionalFields();
		if (optional_fields.size() == 0)
		{
			return;
		}
		FieldSelectDialog field_select_dialog(optional_fields);
		field_select_dialog.exec();

		std::vector<Field> selected_fields = field_select_dialog.selectedFields();
		std::vector<Field>::const_iterator it;
		for (it = selected_fields.begin(); it != selected_fields.end(); ++it)
		{
			addFieldItem(item, item->child(item->childCount()-1), *it);
		}
	}
}

void ProtocolTree::onDelete()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL)
	{
		return;
	}

	EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
	if (item_type == E_ITEM_TYPE_CATEGORY)
	{
		sstring name = item->data(1, Qt::UserRole).toString().toStdString();
		std::map<sstring, int>::iterator it;
		it = m_multi_category_count.find(name);
		if (it != m_multi_category_count.end())
		{
			--it->second;
		}
	}
	else if (item_type == E_ITEM_TYPE_FIELD)
	{
		//
	}
	else
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

QTreeWidgetItem* ProtocolTree::addFieldItem(QTreeWidgetItem* parent,
		QTreeWidgetItem * preceding, const Field& field)
{
//	QStringList text_list;
//	text_list << field.text().c_str() << ""<<""<<field.typeString().c_str()<< QString("%1").arg(field.length())<< field.tip().c_str();
	QTreeWidgetItem *item = new QTreeWidgetItem(parent, preceding);
	item->setText(0, field.text().c_str());
	item->setText(3, field.typeString().c_str());
	item->setText(4, QString("%1").arg(field.length()));
	item->setText(5, field.tip().c_str());
	item->setData(0, Qt::UserRole, QVariant(E_ITEM_TYPE_FIELD));
	item->setData(1, Qt::UserRole, QVariant(field.name().c_str()));
	item->setTextAlignment(3, Qt::AlignHCenter | Qt::AlignVCenter);

	ProtocolTreeItem* tree_item = new ProtocolTreeItem(item, field);
	if (field.type() == E_FIELD_TYPE_STRING)
	{
		connect(tree_item, SIGNAL(textChange(QTreeWidgetItem *, int)), this,
				SLOT(itemWidgetTextChange(QTreeWidgetItem *, int)));
	}
	setItemWidget(item, 1, tree_item);

	if (field.defaultValue() == K_DEFAULT_VALUE_DEFAULT)
	{
		QCheckBox* checkbox = new QCheckBox(this);
		setItemWidget(item, 2, checkbox);
		connect(checkbox, SIGNAL(stateChanged (int)), tree_item,
				SLOT(checkBoxStateChange(int)));
		tree_item->setEnabled(false);
	}

	item->setIcon(0, QIcon(field.icon().c_str()));

	return item;
}

QTreeWidgetItem * ProtocolTree::addCategoryItem(QTreeWidget * parent,
		QTreeWidgetItem * category_preceding, const Category& category)
{
//	QStringList text_list;
//	text_list << category.text().c_str()<<""<<""<<""<<category.tip().c_str();
	QTreeWidgetItem *category_item = new QTreeWidgetItem(parent,
			category_preceding);
	category_item->setText(0, category.text().c_str());
	category_item->setText(5, category.tip().c_str());
	category_item->setData(0, Qt::UserRole, QVariant(E_ITEM_TYPE_CATEGORY));
	category_item->setData(1, Qt::UserRole, QVariant(category.name().c_str()));
	category_item->setIcon(0, QIcon(":/npg/category"));

	const std::vector<Field>& fields = category.fields();
	std::vector<Field>::const_iterator it_field;
	QTreeWidgetItem * field_preceding = NULL;
	for (it_field = fields.begin(); it_field != fields.end(); ++it_field)
	{
		if (!it_field->isOptional())
		{
			field_preceding = addFieldItem(category_item, field_preceding,
					*it_field);
		}
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
			m_multi_category_count.insert(std::make_pair(category.name(), 1));
		}
	}

	return category_item;
}

void ProtocolTree::itemWidgetTextChange(QTreeWidgetItem *item, int count)
{
	item->setText(4, QString("%1").arg(count));
}

//void ProtocolTree::mousePressEvent(QMouseEvent *event)
//{
//	if (event->button() == Qt::LeftButton)
//	{
//		m_start_pos = event->pos();
//	}
//	QTreeWidget::mousePressEvent(event);
//
//}
//void ProtocolTree::mouseMoveEvent(QMouseEvent *event)
//{
//	if (event->button() == Qt::LeftButton)
//	{
//		int distance = (event->pos() - m_start_pos).manhattanLength();
//		if (distance >= QApplication::startDragDistance())
//		{
//			performDrag();
//		}
//	}
//	QTreeWidget::mouseMoveEvent(event);
//}
//
//void ProtocolTree::performDrag()
//{
//	QTreeWidgetItem* item = currentItem();
//	if (item == NULL)
//	{
//		return;
//	}
//	EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
//	if (item_type == E_ITEM_TYPE_CATEGORY)
//	{
//		return;
//	}
//
//	QTreeWidgetItem* item_parent = item->parent();
//	QString category_name = item_parent->data(1, Qt::UserRole).toString();
//	QString field_name = item->data(1, Qt::UserRole).toString();
//
//	Field field = m_protocol.category(category_name.toStdString()).field(field_name.toStdString());
//
//	QMimeData* mine_data = new QMimeData();
//	mine_data->setText(field.name().c_str());
//	mine_data->setHtml(category_name);
//	QDrag* drag = new QDrag(this);
//	drag->setMimeData(mine_data);
//	drag->setPixmap(QPixmap(field.icon().c_str()));
//	if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
//	{
//		delete item;
//	}
//}
//
//void ProtocolTree::dragMoveEvent(QDragMoveEvent *event)
//{
//	ProtocolTree* source = qobject_cast<ProtocolTree*>(event->source());
//	if (source != NULL && source == this)
//	{
//		QTreeWidgetItem* item = itemAt(event->pos());
//		if (item == NULL)
//		{
//			return;
//		}
//		EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
//		if (item_type == E_ITEM_TYPE_CATEGORY)
//		{
//			return;
//		}
//
//		QTreeWidgetItem* item_parent = item->parent();
//		QString category_name = item_parent->data(1, Qt::UserRole).toString();
//		//QString field_name = item->data(1, Qt::UserRole).toString();
//		if (event->mimeData()->html() != category_name)
//		{
//			return;
//		}
//
//		event->setDropAction(Qt::MoveAction);
//		event->accept();
//	}
//}
//void ProtocolTree::dragEnterEvent(QDragEnterEvent *event)
//{
//	ProtocolTree* source = qobject_cast<ProtocolTree*>(event->source());
//	if (source != NULL && source == this)
//	{
//		event->setDropAction(Qt::MoveAction);
//		event->accept();
//	}
//}
//void ProtocolTree::dropEvent(QDropEvent *event)
//{
	//const QMimeData* data = event->mimeData();
//	ProtocolTree* source = qobject_cast<ProtocolTree*>(event->source());
//	if (source != NULL && source == this)
//	{
//		QTreeWidgetItem* item = itemAt(event->pos());
//		if (item == NULL)
//		{
//			return;
//		}
//
//		EItemType item_type = (EItemType) item->data(0, Qt::UserRole).toInt();
//		if (item_type == E_ITEM_TYPE_CATEGORY)
//		{
//			return;
//		}
//
//		QTreeWidgetItem* item_parent = item->parent();
//		QString category_name = item_parent->data(1, Qt::UserRole).toString();
//		QString field_name = item->data(1, Qt::UserRole).toString();
//
//		Field field = m_protocol.category(category_name.toStdString()).field(field_name.toStdString());
//
//		addFieldItem(item_parent, item, field);
//		event->setDropAction(Qt::MoveAction);
//		event->accept();
//	}
//}