#include "protocol_tree_item_widget.h"
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <QComboBox>
#include "number_combobox.h"
#include "number_edit.h"
#include "logger.h"

ProtocolTreeItemWidget::ProtocolTreeItemWidget(QTreeWidgetItem *item, const Field& field, QWidget *parent)
:
		QWidget(parent), m_field(field), m_item(item)
{
	ui.setupUi(this);
	m_child = getFieldWidget(m_field);
	ui.layout->addWidget(m_child, 0, 0);
	if (!field.editable()) {
		QComboBox* widget = dynamic_cast<QComboBox*>(m_child);
		if (widget != NULL) {
			widget->setEditable(false);
		} else {
			this->setEnabled(false);
		}
	}

	if(field.defaultValue().length() > 0){
		setText(field.defaultValue());
	}
}

ProtocolTreeItemWidget::~ProtocolTreeItemWidget()
{

}

QWidget* ProtocolTreeItemWidget::getFieldWidget(const Field& field) {
	if (!field.isItemsEmpty()) {
		return getComboBoxWidget(field);
	}

	QWidget* widget = NULL;

	if (!field.isSubFieldsEmpty()) {
		QLabel* label = new QLabel(field.defaultValue());
		label->setAlignment(Qt::AlignCenter);
		widget = label;
	} else if (field.type() == E_FIELD_TYPE_INT || field.type() == E_FIELD_TYPE_BIT) {
		widget = new NumberEdit(field);
	} else if (field.type() == E_FIELD_TYPE_STRING) {
		QLineEdit* edit = new QLineEdit(field.defaultValue());
		connect(edit, SIGNAL(textChanged ( const QString & )), this, SLOT(onTextChange()));
		widget = edit;
	} else if (field.type() == E_FIELD_TYPE_MAC) {
		QLineEdit* edit = new QLineEdit(field.defaultValue());
		widget = edit;
	} else if (field.type() == E_FIELD_TYPE_IP) {
		QLineEdit* edit = new QLineEdit(field.defaultValue());
		edit->setInputMask("000.000.000.000");
		widget = edit;
	} else {
		QLabel* label = new QLabel(field.defaultValue());
		label->setAlignment(Qt::AlignCenter);
		widget = label;
		LOG_ERROR(tr("invaild field type: %1").arg(field.type()));
	}

	return widget;
}

QWidget* ProtocolTreeItemWidget::getComboBoxWidget(const Field& field) {
	QWidget* widget = NULL;

	if (field.type() == E_FIELD_TYPE_INT || field.type() == E_FIELD_TYPE_BIT) {
		widget = new NumberComboBox(field);
	} else if (field.type() == E_FIELD_TYPE_STRING) {
		QComboBox* combobox = new QComboBox();
		addDataToComboBox(combobox, field);
		connect(combobox, SIGNAL(textChanged ( const QString & )), this, SLOT(onTextChange()));
		widget = combobox;
	} else if (field.type() == E_FIELD_TYPE_MAC) {
		QComboBox* combobox = new QComboBox();
		addDataToComboBox(combobox, field);
		widget = combobox;
	} else if (field.type() == E_FIELD_TYPE_IP) {
		QComboBox* combobox = new QComboBox();
//		combobox->setInputMask("000.000.000.000");
		addDataToComboBox(combobox, field);
		widget = combobox;
	} else {
		QLabel* label = new QLabel(field.defaultValue());
		label->setAlignment(Qt::AlignCenter);
		widget = label;
	}

	return widget;
}

void ProtocolTreeItemWidget::addDataToComboBox(QComboBox* combobox, const Field& field) {
	const std::vector<FieldItem>& field_items = field.items();
	std::vector<FieldItem>::const_iterator it;
	for (it = field_items.begin(); it != field_items.end(); ++it) {
		combobox->addItem(it->value());
	}
	combobox->setEditable(true);
}

QString ProtocolTreeItemWidget::value()
{
	NumberComboBox * number_box;
	NumberEdit * number_edit;
	QLineEdit * line_edit;
	QComboBox * combobox;
	if ((number_box = dynamic_cast<NumberComboBox*>(m_child)) != NULL) {
		return number_box->getIntValue();
	} else if ((number_edit = dynamic_cast<NumberEdit*>(m_child)) != NULL) {
		return number_edit->getIntValue();
	} else if ((line_edit = dynamic_cast<QLineEdit*>(m_child)) != NULL) {
		return line_edit->text();
	} else if ((combobox = dynamic_cast<QComboBox*>(m_child)) != NULL) {
		return combobox->currentText();
	} else {
		return ((QLabel*) m_child)->text();
	}
}

QString ProtocolTreeItemWidget::text()
{
	QLineEdit * line_edit;
	QComboBox * combobox;
	if ((line_edit = dynamic_cast<QLineEdit*>(m_child)) != NULL) {
		return line_edit->text();
	} else if ((combobox = dynamic_cast<QComboBox*>(m_child)) != NULL) {
		return combobox->currentText();
	} else {
		return ((QLabel*) m_child)->text();
	}

}

void ProtocolTreeItemWidget::setText(const QString& value) {
	QLineEdit * line_edit;
	QComboBox * combobox;
	if ((line_edit = dynamic_cast<QLineEdit*>(m_child)) != NULL) {
		line_edit->setText(value);
	} else if ((combobox = dynamic_cast<QComboBox*>(m_child)) != NULL) {
		if (m_field.editable()) {
			combobox->setEditText(value);
		} else {
			int index = combobox->findText(value);
			if (index != -1) {
				combobox->setCurrentIndex(index);
			}
		}
	} else {
		((QLabel*) m_child)->setText(value);
	}
}

void ProtocolTreeItemWidget::onTextChange()
{
	QTextEdit* text_edit = dynamic_cast<QTextEdit*>(m_child);
	if (text_edit != NULL) {
		emit textChange(m_item, text_edit->toPlainText().length());
		return;
	}

	QLineEdit* line_edit = dynamic_cast<QLineEdit*>(m_child);
	if (line_edit != NULL) {
		emit textChange(m_item, line_edit->text().length());
		return;
	}

}

void ProtocolTreeItemWidget::onCheckBoxStateChange(int state) {
	if (state == Qt::Checked) {
		this->setEnabled(true);
		setText("");
	} else {
		this->setEnabled(false);
		setText(this->m_field.defaultValue());
	}
}
