#include "protocol_tree_item_widget.h"
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <QComboBox>

ProtocolTreeItemWidget::ProtocolTreeItemWidget(QTreeWidgetItem *item, const Field& field, QWidget *parent)
	:QWidget(parent), m_field(field), m_item(item)
{
	ui.setupUi(this);
	m_child = getFieldWidget(m_field);
	ui.layout->addWidget(m_child, 0, 0);
	if (!field.editable())
	{
		if (field.inputMethod() == E_FIELD_INPUT_METHOD_SELECT)
		{
			((QComboBox*)m_child)->setEditable(false);
		}
		else
		{
			this->setEnabled(false);
		}
	}
}

ProtocolTreeItemWidget::~ProtocolTreeItemWidget()
{

}

QWidget* ProtocolTreeItemWidget::getFieldWidget(const Field& field)
{
	QWidget* widget = NULL;

	if (field.inputMethod() == E_FIELD_INPUT_METHOD_LINEEDIT)
	{
		QLineEdit* edit = new QLineEdit(field.defaultValue());
		switch (field.type())
		{
			
		case E_FIELD_TYPE_BIT://No precise limits, the excess part will be truncated
			edit->setValidator(new QIntValidator(this));	
			break;
		case E_FIELD_TYPE_INT:
			edit->setValidator(new QIntValidator(field.minValue(), field.maxValue(), this));	
			break;
		case E_FIELD_TYPE_IP:
			edit->setInputMask("000.000.000.000");
			break;
		case E_FIELD_TYPE_MAC:
			//edit->setInputMask("NN:NN:NN:NN:NN:NN");
			break;
		default:
			break;
		}
		widget = edit;
		if (field.type() == E_FIELD_TYPE_STRING)
		{
			connect(edit, SIGNAL(textChanged ( const QString &  )), this, SLOT(onTextChange()));
		}	
	}
	else if (field.inputMethod() == E_FIELD_INPUT_METHOD_TEXTEDIT)
	{
		QTextEdit* edit = new QTextEdit(field.defaultValue());
		widget = edit;
		if (field.type() == E_FIELD_TYPE_STRING)
		{
			connect(edit, SIGNAL(textChanged ()), this, SLOT(onTextChange()));
		}
	}
	else if(field.inputMethod() == E_FIELD_INPUT_METHOD_SELECT) 
	{
		QComboBox* combo_box = new QComboBox(this);
		const std::vector<FieldItem>& field_items = field.items();
		std::vector<FieldItem>::const_iterator it;
		for (it = field_items.begin(); it != field_items.end(); ++it)
		{
			QString text = it->text();
			if (field.type() != E_FIELD_TYPE_STRING)
			{
				text = QString("%1 (%2)").arg(it->text()).arg(it->value());
			}
			combo_box->addItem(text, QVariant(it->value()));
		}
		combo_box->setEditable(true);
		widget = combo_box;
	}
	else
	{
		QLabel* label = new QLabel(field.defaultValue());
		label->setAlignment(Qt::AlignCenter);
		widget = label;
	}

	return widget;
}

QString ProtocolTreeItemWidget::value()
{
	QString value;

	switch (m_field.inputMethod())
	{
	case E_FIELD_INPUT_METHOD_LINEEDIT:
		value = ((QLineEdit*)m_child)->text();
		break;
	case E_FIELD_INPUT_METHOD_TEXTEDIT:
		value = ((QTextEdit*)m_child)->toPlainText();
		break;
	case E_FIELD_INPUT_METHOD_SELECT:
		{
			QComboBox* child = (QComboBox*)m_child;
			int index = child->findText(child->currentText());
			if (index == -1)
			{
				value = child->currentText();
			}
			else
			{
				value = child->itemData(index).toString();
			}
		}
		break;
	default:
		value = ((QLabel*)m_child)->text();
		break;
	}

	return value;
}

void ProtocolTreeItemWidget::setValue(const QString& value)
{
	switch (m_field.inputMethod())
	{
	case E_FIELD_INPUT_METHOD_LINEEDIT:
		((QLineEdit*)m_child)->setText(value);
		break;
	case E_FIELD_INPUT_METHOD_SELECT:
		((QComboBox*)m_child)->setEditText(value);
		break;
	case E_FIELD_INPUT_METHOD_TEXTEDIT:
		((QTextEdit*)m_child)->setText(value);
		break;
	default:
		((QLabel*)m_child)->setText(value);
		break;
	}
}

void ProtocolTreeItemWidget::onTextChange()
{
	QTextEdit* text_edit = dynamic_cast<QTextEdit*>(m_child);
	if (text_edit != NULL)
	{
		emit textChange(m_item, text_edit->toPlainText().length());
		return;
	}

	QLineEdit* line_edit = dynamic_cast<QLineEdit*>(m_child);
	if (line_edit != NULL)
	{
		emit textChange(m_item, line_edit->text().length());
		return;
	}
	
}


void ProtocolTreeItemWidget::checkBoxStateChange(int state)
{
	if (state == Qt::Checked)
	{
		this->setEnabled(true);
		setValue("");
	}
	else
	{
		this->setEnabled(false);
		setValue(K_DEFAULT_VALUE_DEFAULT);
	}
}