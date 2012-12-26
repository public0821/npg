#include "protocol_tree.h"
#include <qmessagebox.h>
#include <qmenu.h>
#include "protocol_tree_item_widget.h"
#include <QCheckBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include "field_select_dialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDomDocument>
#include <QFile>
#include <QTextStream>
#include "../qresource.h"

const int FIELD_COUNT = 6;
const int INDEX_FIELD_NAME = 0;
const int INDEX_FIELD_VALUE = 1;
const int INDEX_FIELD_IS_DEFAULT = 2;
const int INDEX_FIELD_TYPE = 3;
const int INDEX_FIELD_LEN = 4;
const int INDEX_FIELD_TIP = 5;

const int ROLEDATA_FIELDTYPE = 0;
const int ROLEDATA_FIELDNAME = 1;

ProtocolTree::ProtocolTree(QWidget *parent) :
		QTreeWidget(parent)
{

}

ProtocolTree::~ProtocolTree()
{

}

void ProtocolTree::setup(Protocol protocol) {
	m_protocol = protocol;
	setColumnCount(6);
	QStringList head_list;
	head_list << tr("field") << tr("value") << "" << tr("type") << tr("length") << tr("tip");
	setHeaderLabels(head_list);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this,
			SLOT(onShowPopup(const QPoint &)));
	setContextMenuPolicy(Qt::CustomContextMenu);
	setDragDropMode(NoDragDrop);
	//setDragDropMode(InternalMove);

	m_delete_action = new QAction(QIcon(ICON_CATEGORY_DELETE),
			tr("Delete(&D)"), this);
	m_delete_action->setShortcut(QKeySequence::fromString("Ctrl+D"));
	m_add_action = new QAction(QIcon(ICON_CATEGORY_ADD), tr("Add(&A)"),
			this);
	m_add_action->setShortcut(QKeySequence::fromString("Ctrl+A"));
	m_add_field_action = new QAction(QIcon(ICON_CATEGORY_ADD),
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
			++it_category) {
		preceding = addCategoryItem(this, preceding, *it_category);
	}

	adjust();

	//viewport()->setBackgroundRole(QPalette::Background);
	//ssetAutoFillBackground(false);
}

void ProtocolTree::adjust()
{
	expandAll();

	for (int i = 0; i < FIELD_COUNT; i++)
	{
		resizeColumnToContents(i);
	}
}

void ProtocolTree::onShowPopup(const QPoint &pos) {
	QTreeWidgetItem * item = itemAt(pos);

	if (item != NULL) {
		EItemType item_type = (EItemType) item->data(ROLEDATA_FIELDTYPE, Qt::UserRole).toInt();
		if (item_type == E_ITEM_TYPE_CATEGORY) {
			QString name = item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
			Category category = m_protocol.category(name);

			QMenu menu(this);
			if (category.isMany()) {
				menu.addAction(m_add_action);
				m_add_action->setEnabled(true);

				menu.addAction(m_delete_action);
				m_delete_action->setEnabled(true);
			}
			if (category.optionalFieldCount() > 0) {
				menu.addAction(m_add_field_action);
				m_add_field_action->setEnabled(true);
			}
			if (!menu.isEmpty()) {
				menu.exec(mapToGlobal(pos));
			}

		} else if (item_type == E_ITEM_TYPE_FIELD) {
			QString category_name =
					item->parent()->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
			QString field_name =
					item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
			Category category = m_protocol.category(category_name);
			Field field = category.field(field_name);
			QMenu menu(this);
			if (field.isOptional()) {
				menu.addAction(m_add_action);
				m_add_action->setEnabled(true);

				menu.addAction(m_delete_action);
				m_delete_action->setEnabled(true);
			}
			if (category.optionalFieldCount() > 0) {
				menu.addAction(m_add_field_action);
				m_add_field_action->setEnabled(true);
			}
			if (!menu.isEmpty()) {
				menu.exec(mapToGlobal(pos));
			}
		}
	}
}

void ProtocolTree::onAdd()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL) {
		return;
	}

	EItemType item_type = (EItemType) item->data(ROLEDATA_FIELDTYPE, Qt::UserRole).toInt();
	if (item_type == E_ITEM_TYPE_CATEGORY) {
		QString name = item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
		Category category = m_protocol.category(name);
		addCategoryItem(this, item, category);
	}
	else if (item_type == E_ITEM_TYPE_FIELD) {
		QString category_name =
				item->parent()->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
		QString field_name =
				item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
		Category category = m_protocol.category(category_name);
		Field field = category.field(field_name);
		addFieldItem(item->parent(), item, field);
	}
}

void ProtocolTree::onAddField()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL) {
		return;
	}

	EItemType item_type = (EItemType) item->data(ROLEDATA_FIELDTYPE, Qt::UserRole).toInt();
	Category category;
	QTreeWidgetItem* category_item;
	QTreeWidgetItem* preceding;
	if (item_type == E_ITEM_TYPE_CATEGORY) {
		QString name = item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
		category = m_protocol.category(name);
		category_item = item;
		preceding = item->child(item->childCount() - 1);
	} else if (item_type == E_ITEM_TYPE_FIELD) {
		QString category_name =
				item->parent()->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
		category = m_protocol.category(category_name);
		category_item = item->parent();
		preceding = item;
	} else {
		return;
	}

	std::vector<Field> optional_fields = category.optionalFields();
	if (optional_fields.size() == 0) {
		return;
	}
	FieldSelectDialog field_select_dialog(optional_fields);
	field_select_dialog.exec();

	std::vector<Field> selected_fields = field_select_dialog.selectedFields();
	std::vector<Field>::const_iterator it;
	for (it = selected_fields.begin(); it != selected_fields.end(); ++it) {
		preceding = addFieldItem(category_item, preceding, *it);
	}

	category_item->setExpanded(false);
	category_item->setExpanded(true);
}

void ProtocolTree::onDelete()
{
	QTreeWidgetItem* item = getSelectedItem();
	if (item == NULL) {
		return;
	}

	EItemType item_type = (EItemType) item->data(ROLEDATA_FIELDTYPE, Qt::UserRole).toInt();
	if (item_type == E_ITEM_TYPE_CATEGORY) {
	}
	else if (item_type == E_ITEM_TYPE_FIELD) {
		//
	}
	else {
		return;
	}

	delete item;
}

QTreeWidgetItem* ProtocolTree::getSelectedItem()
{
	QList<QTreeWidgetItem*> items = selectedItems();
	if (items.count() == 0) {
		QMessageBox::information(this, tr("tip"), tr("please select a node"));
		return NULL;
	}
	if (items.count() > 1) {
		QMessageBox::information(this, tr("tip"), tr("only can select one node"));
		return NULL;
	}

	return items.at(0);
}

QTreeWidgetItem* ProtocolTree::addSingleFieldItem(QTreeWidgetItem* parent, QTreeWidgetItem * preceding, const Field& field) {
	QTreeWidgetItem *item = new QTreeWidgetItem(parent, preceding);
	item->setText(INDEX_FIELD_NAME, field.text());
	item->setText(INDEX_FIELD_TYPE, field.typeString());
	item->setText(INDEX_FIELD_LEN, QString("%1").arg(field.length()));
	item->setText(INDEX_FIELD_TIP, field.tip());
	item->setData(ROLEDATA_FIELDTYPE, Qt::UserRole, QVariant(E_ITEM_TYPE_FIELD));
	item->setData(ROLEDATA_FIELDNAME, Qt::UserRole, QVariant(field.name()));
	item->setTextAlignment(INDEX_FIELD_TYPE, Qt::AlignHCenter | Qt::AlignVCenter);

	ProtocolTreeItemWidget* tree_item = new ProtocolTreeItemWidget(item, field);
	if (field.type() == E_FIELD_TYPE_STRING) {
		connect(tree_item, SIGNAL(textChange(QTreeWidgetItem *, int)), this,
				SLOT(onItemWidgetTextChange(QTreeWidgetItem *, int)));
		onItemWidgetTextChange(item, field.defaultValue().toLocal8Bit().length());
	}
	setItemWidget(item, 1, tree_item);

	if (field.defaultValue().length() > 0 && field.editable()) {
		QCheckBox* checkbox = new QCheckBox(this);
		setItemWidget(item, INDEX_FIELD_IS_DEFAULT, checkbox);
		connect(checkbox, SIGNAL(stateChanged (int)), tree_item,
				SLOT(onCheckBoxStateChange(int)));
		tree_item->setEnabled(false);
	}

	item->setIcon(0, QIcon(field.icon()));

	return item;
}

QTreeWidgetItem* ProtocolTree::addFieldItem(QTreeWidgetItem* parent,
		QTreeWidgetItem * preceding, const Field& field) {
//	QStringList text_list;
//	text_list << field.text().c_str() << ""<<""<<field.typeString().c_str()<< QString("%1").arg(field.length())<< field.tip().c_str();
	QTreeWidgetItem *item = addSingleFieldItem(parent, preceding, field);

	const std::vector<Field>& sub_fields = field.subFields();
	std::vector<Field>::const_iterator it;
	for (it = sub_fields.begin(); it != sub_fields.end(); it++) {
		addSubFieldItem(item, *it);
	}

	return item;
}

QTreeWidgetItem* ProtocolTree::addSubFieldItem(QTreeWidgetItem* parent, const Field& field) {
	if (field.type() != E_FIELD_TYPE_BIT) {
		QMessageBox::information(this, tr("tip"), QString(tr("unsupported sub field type")) + field.typeString());
		return NULL;
	}

	//	QStringList text_list;
	//	text_list << field.text().c_str() << ""<<""<<field.typeString().c_str()<< QString("%1").arg(field.length())<< field.tip().c_str();
	QTreeWidgetItem *item = new QTreeWidgetItem(parent);
	item->setText(INDEX_FIELD_NAME, field.text());
	item->setText(INDEX_FIELD_TYPE, field.typeString());
	item->setText(INDEX_FIELD_LEN, QString("%1").arg(field.length()));
	item->setText(INDEX_FIELD_TIP, field.tip());
	item->setData(ROLEDATA_FIELDTYPE, Qt::UserRole, QVariant(E_ITEM_TYPE_SUBFIELD));
	item->setData(ROLEDATA_FIELDNAME, Qt::UserRole, QVariant(field.name()));
	item->setTextAlignment(INDEX_FIELD_TYPE, Qt::AlignHCenter | Qt::AlignVCenter);

	ProtocolTreeItemWidget* tree_item = new ProtocolTreeItemWidget(item, field);
	setItemWidget(item, 1, tree_item);

	if (field.defaultValue().length() > 0 && field.editable()) {
		QCheckBox* checkbox = new QCheckBox(this);
		setItemWidget(item, INDEX_FIELD_IS_DEFAULT, checkbox);
		connect(checkbox, SIGNAL(stateChanged (int)), tree_item,
				SLOT(onCheckBoxStateChange(int)));
		tree_item->setEnabled(false);
	}

	item->setIcon(0, QIcon(field.icon()));

	return item;
}

QTreeWidgetItem * ProtocolTree::addSingleCategoryItem(QTreeWidget * parent, QTreeWidgetItem * category_preceding, const Category& category) {
	QTreeWidgetItem *category_item = new QTreeWidgetItem(parent,
			category_preceding);

	category_item->setText(INDEX_FIELD_NAME, category.text());
	category_item->setText(INDEX_FIELD_TIP, category.tip());
	category_item->setData(ROLEDATA_FIELDTYPE, Qt::UserRole, QVariant(E_ITEM_TYPE_CATEGORY));
	category_item->setData(ROLEDATA_FIELDNAME, Qt::UserRole, QVariant(category.name()));
	category_item->setIcon(0, QIcon(ICON_CATEGORY));

	return category_item;
}

QTreeWidgetItem * ProtocolTree::addCategoryItem(QTreeWidget * parent,
		QTreeWidgetItem * category_preceding, const Category& category) {
//	QStringList text_list;
//	text_list << category.text().c_str()<<""<<""<<""<<category.tip().c_str();
	QTreeWidgetItem *category_item = addSingleCategoryItem(parent, category_preceding, category);

	const std::vector<Field>& fields = category.fields();
	std::vector<Field>::const_iterator it_field;
	QTreeWidgetItem * field_preceding = NULL;
	for (it_field = fields.begin(); it_field != fields.end(); ++it_field) {
		if (!it_field->isOptional() || it_field->isShowOnStart()) {
			field_preceding = addFieldItem(category_item, field_preceding,
					*it_field);
		}
	}

	return category_item;
}

void ProtocolTree::onItemWidgetTextChange(QTreeWidgetItem *item, int count) {
	ProtocolTreeItemWidget* value_item = (ProtocolTreeItemWidget*) this->itemWidget(item, INDEX_FIELD_VALUE);
	if (value_item != NULL) {
		item->setText(INDEX_FIELD_LEN, QString("%1").arg(value_item->value().toLocal8Bit().length()));
	}
}

void ProtocolTree::onSaveSettings() {
	QString file_name = QFileDialog::getSaveFileName(this, tr("Select config file"), QDir::currentPath(), tr("XML files (*.xml)"));
	if (file_name.isEmpty()) {
		return;
	}

	QDomDocument document;
	document.setContent(QString("<?xml version=\"1.0\" encoding=\"utf-8\"?>"));
	QDomElement root = document.createElement("Protocol");
	document.appendChild(root);

	int category_count = this->topLevelItemCount();
	for (int index_category = 0; index_category < category_count; index_category++) {
		QTreeWidgetItem* category_item = this->topLevelItem(index_category);
		QDomElement category_element = document.createElement("Category");
		QString category_name = category_item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
		category_element.setAttribute("Name", category_name);

		for (int index_field = 0; index_field < category_item->childCount(); index_field++) {
			QTreeWidgetItem* field_item = category_item->child(index_field);
			QDomElement field_element = document.createElement("Field");
			QString field_name = field_item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
			field_element.setAttribute("Name", field_name);
			ProtocolTreeItemWidget* value_item = (ProtocolTreeItemWidget*) this->itemWidget(field_item, INDEX_FIELD_VALUE);
			field_element.setAttribute("Data", value_item->text());
			QCheckBox* item_checkbox = (QCheckBox*) this->itemWidget(field_item, INDEX_FIELD_IS_DEFAULT);
			if (item_checkbox != NULL && item_checkbox->checkState() == Qt::Checked) {
				field_element.setAttribute("Checked", "true");
			}

			category_element.appendChild(field_element);

			int sub_field_count = field_item->childCount();
			for (int index_sub_field = 0; index_sub_field < sub_field_count; index_sub_field++) {
				QTreeWidgetItem* sub_field_item = field_item->child(index_sub_field);
				QDomElement sub_field_element = document.createElement("SubField");
				QString sub_field_name = sub_field_item->data(ROLEDATA_FIELDNAME, Qt::UserRole).toString();
				sub_field_element.setAttribute("Name", sub_field_name);
				ProtocolTreeItemWidget* value_item = (ProtocolTreeItemWidget*) this->itemWidget(sub_field_item, INDEX_FIELD_VALUE);
				sub_field_element.setAttribute("Data", value_item->text());
				QCheckBox* item_checkbox = (QCheckBox*) this->itemWidget(sub_field_item, INDEX_FIELD_IS_DEFAULT);
				if (item_checkbox != NULL && item_checkbox->checkState() == Qt::Checked) {
					sub_field_element.setAttribute("Checked", "true");
				}
				field_element.appendChild(sub_field_element);
			}
		}

		root.appendChild(category_element);
	}

	QFile file(file_name);
	file.open(QIODevice::WriteOnly);
	QTextStream t(&file);
	t << document.toString();
	file.close();
}

void ProtocolTree::onRestoreSettings()
{
	QString file_name = QFileDialog::getOpenFileName(this, tr("Select config file"), QDir::currentPath(), tr("XML files (*.xml)"));
	if (file_name.isEmpty()) {
		return;
	}

	QFile file(file_name);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QString errorString = tr("Error: Cannot read file %1: %2");
		errorString = errorString.arg(file_name, file.errorString());
		QMessageBox::critical(NULL, tr("tip"), errorString);
		return;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;
	QDomDocument doc;
	if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
		QString errorString = tr("Error: Parse error at line %1, column %2: %3");
		errorString = errorString.arg(errorLine).arg(errorColumn).arg(errorStr);
		QMessageBox::critical(NULL, tr("tip"), errorString);
		return;
	}

	QDomElement root_element = doc.documentElement();
	if (root_element.tagName() != "Protocol") {
		QMessageBox::critical(NULL, tr("tip"), QString(tr("The file %1 is not an config file.")).arg(file_name));
		return;
	}

	this->clear();
	QDomElement category_element = root_element.firstChildElement("Category");
	QTreeWidgetItem *category_preceding = NULL;
	while (!category_element.isNull()) {
		QString category_name = category_element.attribute("Name");
		Category category = m_protocol.category(category_name);
		if (category.empty()) {
			category_element = category_element.nextSiblingElement("Category");
			continue;
		}
		QTreeWidgetItem *category_item = addSingleCategoryItem(this, category_preceding, category);
		category_preceding = category_item;

		QDomElement field_element = category_element.firstChildElement("Field");
		QTreeWidgetItem * field_preceding = NULL;
		while (!field_element.isNull()) {
			QString field_name = field_element.attribute("Name");
			Field field = category.field(field_name);
			if (field.empty()) {
				field_element = field_element.nextSiblingElement("Field");
				continue;
			}
			QTreeWidgetItem *field_item = addSingleFieldItem(category_item, field_preceding, field);
			field_preceding = field_item;

			QCheckBox* item_checkbox = (QCheckBox*) this->itemWidget(field_item, INDEX_FIELD_IS_DEFAULT);
			if (item_checkbox != NULL && field_element.attribute("Checked") == "true") {
				item_checkbox->setCheckState(Qt::Checked);
			}
			ProtocolTreeItemWidget* value_item = (ProtocolTreeItemWidget*) this->itemWidget(field_item, INDEX_FIELD_VALUE);
			value_item->setText(field_element.attribute("Data"));

			QDomElement sub_field_element = field_element.firstChildElement("SubField");
			while (!sub_field_element.isNull()) {
				QString sub_field_name = sub_field_element.attribute("Name");
				Field sub_field = field.subField(sub_field_name);
				if (sub_field.empty()) {
					sub_field_element = sub_field_element.nextSiblingElement("SubField");
					continue;
				}
				QTreeWidgetItem *sub_field_item = addSubFieldItem(field_item, sub_field);
				QCheckBox* item_checkbox = (QCheckBox*) this->itemWidget(sub_field_item, INDEX_FIELD_IS_DEFAULT);
				if (item_checkbox != NULL && sub_field_element.attribute("Checked") == "true") {
					item_checkbox->setCheckState(Qt::Checked);
				}
				ProtocolTreeItemWidget* value_item = (ProtocolTreeItemWidget*) this->itemWidget(sub_field_item, INDEX_FIELD_VALUE);
				value_item->setText(sub_field_element.attribute("Data"));

				sub_field_element = sub_field_element.nextSiblingElement("SubField");
			}

			field_element = field_element.nextSiblingElement("Field");
		}
		category_element = category_element.nextSiblingElement("Category");
	}

	adjust();
}
