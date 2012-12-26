#include "field.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "lib/os.h"
#include "../qresource.h"


QString FieldDefaultValue::SECOND = "second";
QString FieldDefaultValue::PID = "pid";
QString FieldDefaultValue::MILLISECOND = "millisecond";
QString FieldDefaultValue::CHECKNUM = "checksum";
QString FieldDefaultValue::SEQ = "seq";

Field::Field(const QString& category_name, bool empty)
:m_type(E_FIELD_TYPE_INT)
, m_length(0)
, m_empty(empty)
, m_optional(false)
, m_editable(true)
, m_category_name(category_name)
, m_show_on_start(false)
{
}

Field::~Field(void)
{
}

bool Field::empty() const
{
	return m_empty;
}

void Field::setName(const QString& name)
{
	m_name = name;
}

void Field::setType(EFiledType type)
{
	m_type = type;
}

void Field::setOptional(bool optional)
{
	m_optional = optional;
}

void Field::setTypeString(QString type_string)
{
	m_type_string = type_string;
}

void Field::setLength(size_t length)
{
	m_length = length;
}

void Field::setText(const QString& text)
{
	m_text = text;
}

void Field::setTip(const QString& tip)
{
	m_tip = tip;
}
void Field::setDefaultValue(const QString& default_value)
{
	m_default_value = default_value;
}

void Field::addItem(const FieldItem& item)
{
	m_items.push_back(item);
}

void Field::setEditable(bool editable)
{
	m_editable = editable;
}
void Field::setShowOnStart(bool show_on_start)
{
	m_show_on_start = show_on_start;
}

void Field::addSubField(const Field& sub_field)
{
	m_sub_fields.push_back(sub_field);
}

void Field::setSuffix(const QString& suffix)
{
	m_suffix = suffix;
}

void Field::setPrefix(const QString& prefix)
{
	m_prefix = prefix;
}



QString Field::name() const
{
	return m_name;
}

EFiledType Field::type() const
{
	return m_type;
}

size_t Field::length() const
{
	if (m_length == 0 && type() == E_FIELD_TYPE_IP)
	{
		return 4u;
	}
	else if (m_length == 0 && type() == E_FIELD_TYPE_MAC)
	{
		return 6u;
	}
	return m_length;
}

QString Field::text() const
{
	if (m_text.isEmpty())
	{
		return m_name;
	}
	return m_text;
}

QString Field::defaultValue() const
{
	return m_default_value;
}

//QString Field::defaultValueOriginal() const
//{
//	return m_default_value;
//}

QString Field::tip() const
{
	return m_tip;
}

QString Field::icon() const
{
	QString icon;
	switch (type())
	{
	case E_FIELD_TYPE_INT:
		icon = ICON_FIELD_INT;
		break;
	case E_FIELD_TYPE_STRING:
		icon = ICON_FIELD_STRING;
		break;
	case E_FIELD_TYPE_IP:
		icon = ICON_FIELD_IP;
		break;
	case E_FIELD_TYPE_MAC:
		icon = ICON_FIELD_MAC;
		break;
	case E_FIELD_TYPE_BIT:
		icon = ICON_FIELD_BIT;
		break;
	default:
		break;
	}

	return icon;
}

QString Field::typeString() const
{
	return m_type_string;
}

bool Field::isOptional() const
{
	return m_optional;
}

const std::vector<FieldItem>& Field::items() const
{
	return m_items;
}

bool Field::editable() const
{
	return m_editable;
}

QString Field::categoryName() const
{
	return m_category_name;
}

bool Field::isShowOnStart() const
{
	return m_show_on_start;
}

const std::vector<Field>& Field::subFields() const
{
	return m_sub_fields;
}

Field Field::subField(const QString& sub_field_name) const
{
	std::vector<Field>::const_iterator it;
	for (it = m_sub_fields.begin(); it != m_sub_fields.end(); ++it)
	{
		if (it->name() == sub_field_name)
		{
			return *it;
		}
	}

	return Field(m_name, true);
}

QString Field::suffix() const
{
	return m_suffix;
}


QString Field::prefix() const
{
	return m_prefix;
}

void Field::clear(){
	m_empty = true;
}

bool Field::isItemsEmpty()const{
	return m_items.size() == 0;
}

bool Field::isSubFieldsEmpty()const{
	return m_sub_fields.size() == 0;
}


int64_t Field::minValue() const
{
	if(type() == E_FIELD_TYPE_BIT){
		return INT64_MIN;
	}
	int64_t min = 0;

	switch (length())
	{
	case 0:
		min = 0;
		break;
	case 1:
		min = INT8_MIN;
		break;
	case 2:
		min = INT16_MIN;
		break;
	case 4:
		min = INT32_MIN;
		break;
	case 8:
    default:
		min = INT64_MIN;
		break;
	}
	return min;
}

int64_t Field::maxValue() const
{
	if(type() == E_FIELD_TYPE_BIT){
		return INT64_MAX;
	}

	uint64_t max = 0;

	switch (length())
	{
	case 0:
		max = 0;
		break;
	case 1:
		max = UINT8_MAX;
		break;
	case 2:
		max = UINT16_MAX;
		break;
	case 4:
		max = UINT32_MAX;
		break;
	case 8:
	default:
		max = INT64_MAX;
		break;
	}

	return max;
}


