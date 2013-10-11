#include "field_select_dialog.h"
#include "../qresource.h"

FieldSelectDialog::FieldSelectDialog(const std::vector<Field>& optional_fields, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
	,m_optional_fields(optional_fields)
	,m_ok(false)
{
	ui.setupUi(this);
	setWindowTitle(tr("Select Field"));
	setWindowIcon(QIcon(ICON_NPG));

	ui.select_all_checkbox->setText(tr("Select All"));
	ui.ok_button->setText(tr("OK"));
	ui.cancel_button->setText(tr("Cancel"));

	connect(ui.ok_button, SIGNAL(released()), this, SLOT(onOk()));
	connect(ui.cancel_button, SIGNAL(released()), this, SLOT(reject()));
	connect(ui.select_all_checkbox, SIGNAL(stateChanged(int)), this, SLOT(onSelectAllChange(int)));

	ui.tree_widget->setColumnCount(4);
	QStringList head_list;
	head_list << tr("field") << tr("type") << tr("length") << tr("tip");
	ui.tree_widget->setHeaderLabels(head_list);
	ui.tree_widget->setDragDropMode(QTreeWidget::NoDragDrop);

	for (size_t index = 0; index < optional_fields.size(); index++)
	{
		QStringList text_list;
		const Field& field = optional_fields[index];
		text_list << field.text() <<field.typeString()<< QString("%1").arg(field.length())<< field.tip();
		QTreeWidgetItem *item = new QTreeWidgetItem(ui.tree_widget, text_list);
		item->setIcon(0, QIcon(field.icon()));
        item->setData(0, Qt::UserRole, QVariant((uint)index));
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


void FieldSelectDialog::onSelectAllChange(int check_state)
{	
	int field_count = ui.tree_widget->topLevelItemCount();
	for (int i = 0; i < field_count; i++)
	{
		QTreeWidgetItem* item = ui.tree_widget->topLevelItem(i);
		if (check_state == Qt::Checked)
		{
			item->setCheckState(0, Qt::Checked);
		}	
		else
		{
			item->setCheckState(0, Qt::Unchecked);
		}
	}
}
