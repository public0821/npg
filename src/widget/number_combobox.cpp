/*
 * number_combobox.cpp
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#include "number_combobox.h"
NumberComboBox::NumberComboBox(QWidget* parent) :
		QComboBox(parent) {
}

NumberComboBox::NumberComboBox(const std::vector<FieldItem>& field_items, QWidget* parent) :
		QComboBox(parent) {
	addItems(field_items);
}

void NumberComboBox::addItems(const std::vector<FieldItem>& field_items) {
	std::vector<FieldItem>::const_iterator it;
	for (it = field_items.begin(); it != field_items.end(); ++it) {
		addItem(it->value(), it->text());
	}
	this->setEditable(true);
}

NumberComboBox::~NumberComboBox() {
	// TODO Auto-generated destructor stub
}

QString NumberComboBox::getIntStrValue() {
	NumberValidator validator;
	int index = this->findText(this->currentText());
	if (index == -1) {
		return QString("%1").arg(validator.value(this->currentText()));
	}

	return QString("%1").arg(validator.value(this->itemData(index).toString()));
}

void NumberComboBox::addItem(int value, QString text, int base) {
	QString str_value;
	str_value.setNum(value, base);
	if(base == 8){
		str_value = QString("0") + str_value;
	}else if(base == 16){
		str_value = QString("0x") + str_value;
	}
	this->addItem(str_value, text);
}

void NumberComboBox::addItem(QString value, QString text) {
	QString full_text = QString("%1 (%2)").arg(value).arg(text);
	QComboBox::addItem(full_text, QVariant(value));
}
