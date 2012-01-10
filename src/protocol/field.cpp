#include "field.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "system/os.h"

Field::Field(const sstring& category_name, bool empty)
:m_type(E_FIELD_TYPE_INT)
, m_input_method(E_FIELD_INPUT_METHOD_NONE)
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

void Field::setName(const sstring& name)
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

void Field::setTypeString(sstring type_string)
{
	m_type_string = type_string;
}

void Field::setInputMethod(EFiledInputMethod input_method)
{
	m_input_method = input_method;
}

void Field::setLength(size_t length)
{
	m_length = length;
}

void Field::setText(const sstring& text)
{
	m_text = text;
}

void Field::setTip(const sstring& tip)
{
	m_tip = tip;
}
void Field::setDefaultValue(const sstring& default_value)
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

void Field::setTail(const sstring& tail)
{
	m_tail = tail;
}

void Field::setPrefix(const sstring& prefix)
{
	m_prefix = prefix;
}



sstring Field::name() const
{
	return m_name;
}

EFiledType Field::type() const
{
	return m_type;
}

EFiledInputMethod Field::inputMethod() const
{
	return m_input_method;
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

sstring Field::text() const
{
	if (m_text.empty())
	{
		return m_name;
	}
	return m_text;
}

sstring Field::defaultValue() const
{
	if (m_default_value == K_DEFAULT_VALUE_SECOND
			|| m_default_value == K_DEFAULT_VALUE_PID
			|| m_default_value == K_DEFAULT_VALUE_MILLISECOND
			|| m_default_value == K_DEFAULT_VALUE_CHECKNUM
			|| m_default_value == K_DEFAULT_VALUE_SEQ)
	{
		//time_t now = time(NULL);
		//char buf[64];
		//bzero(buf, sizeof(buf));
		//snprintf(buf, sizeof(buf), "%ld", now);
		//return buf;
		return K_DEFAULT_VALUE_DEFAULT;
	}
	return m_default_value;

}

sstring Field::defaultValueOriginal() const
{
	return m_default_value;
}

sstring Field::tip() const
{
	return m_tip;
}

int64_t Field::minValue() const
{
	int64_t min;

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

u_int64_t Field::maxValue() const
{
	u_int64_t max;

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
		max = UINT64_MAX;
		break;
	}

	return max;
}

sstring Field::icon() const
{
	sstring icon;
	switch (type())
	{
	case E_FIELD_TYPE_INT:
		icon = ":/npg/field_int";
		break;
	case E_FIELD_TYPE_STRING:
		icon = ":/npg/field_string";
		break;
	case E_FIELD_TYPE_IP:
		icon = ":/npg/field_ip";
		break;
	case E_FIELD_TYPE_MAC:
		icon = ":/npg/field_mac";
		break;
	case E_FIELD_TYPE_BIT:
		icon = ":/npg/field_bit";
		break;
	default:
		break;
	}

	return icon;
}

sstring Field::typeString() const
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

sstring Field::categoryName() const
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

Field Field::subField(const sstring& sub_field_name) const
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

sstring Field::tail() const
{
	return m_tail;
}


sstring Field::prefix() const
{
	return m_prefix;
}