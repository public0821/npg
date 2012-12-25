/*
 * number_combobox.cpp
 *
 *  Created on: 2012-12-24
 *      Author: Young <public0821@gmail.com>
 */

#include "number_combobox.h"

NumberComboBox::NumberComboBox(const Field& field, QWidget* parent) :
		QComboBox(parent), m_field(field){
	// TODO Auto-generated constructor stub
	const std::vector<FieldItem>& field_items = field.items();
	std::vector<FieldItem>::const_iterator it;
	for (it = field_items.begin(); it != field_items.end(); ++it) {
		QString text = it->text();
		this->addItem(text, QVariant(it->value()));
	}
	this->setEditable(true);
}

NumberComboBox::~NumberComboBox()
{
	// TODO Auto-generated destructor stub
}

QString NumberComboBox::getIntValue(){
	return "";
}

