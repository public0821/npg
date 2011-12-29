#include "field_select_dialog.h"

FieldSelectDialog::FieldSelectDialog(const std::vector<Field>& optional_fields, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
	,m_optional_fields(optional_fields)
	,m_ok(false)
{
	ui.setupUi(this);
	setWindowTitle(tr("Select Field"));
	setWindowIcon(QIcon(":/npg/npg"));

	ui.ok_button->setText(tr("OK"));
	ui.cancel_button->setText(tr("Cancel"));
	connect(ui.ok_button, SIGNAL(released()), this, SLOT(onOk()));
	connect(ui.cancel_button, SIGNAL(released()), this, SLOT(close()));

	ui.tree_widget->setColumnCount(4);
	QStringList head_list;
	head_list << "field" << "type" << "length" << "tip";
	ui.tree_widget->setHeaderLabels(head_list);
	ui.tree_widget->setDragDropMode(QTreeWidget::NoDragDrop);

	for (size_t index = 0; index < optional_fields.size(); index++)
	{
		QStringList text_list;
		const Field& field = optional_fields[index];
		text_list << field.text().c_str() <<field.typeString().c_str()<< QString("%1").arg(field.length())<< field.tip().c_str();
		QTreeWidgetItem *item = new QTreeWidgetItem(ui.tree_widget, text_list);
		item->setIcon(0, QIcon(field.icon().c_str()));
		item->setData(0, Qt::UserRole, QVariant(index));
		item->setTextAlignment(2, Qt::AlignHCenter | Qt::AlignVCenter);
		item->setFlags(item->flags()|Qt::ItemIsUserCheckable);
		item->setCheckState(0, Qt::Unchecked);
	}

	ui.tree_widget->expandAll();
	ui.tree_widget->resizeColumnToContents(0);
	ui.tree_widget->resizeColumnToContents(1);
	ui.tree_widget->resizeColumnToContents(2);
	ui.tree_widget->resizeColumnToContents(3);
}

FieldSelectDialog::~FieldSelectDialog()
{

}


void FieldSelectDialog::onOk()
{
	m_ok = true;
	close();
}

std::vector<Field> FieldSelectDialog::selectedFields()
{
	if (!m_ok)
	{
		return std::vector<Field>();
	}

	std::vector<Field> selected_fields;
	int field_count = ui.tree_widget->topLevelItemCount();
	for (int i = 0; i < field_count; i++)
	{
		QTreeWidgetItem* item = ui.tree_widget->topLevelItem(i);
		if (item->checkState(0) == Qt::Checked)
		{
			int index = item->data(0, Qt::UserRole).toInt();
			selected_fields.push_back(m_optional_fields[index]);
		}	
	}
	return selected_fields;
}
