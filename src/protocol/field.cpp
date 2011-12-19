#include "field.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "system/os.h"

Field::Field(void)
:m_type(E_FIELD_TYPE_INT)
,m_input_method(E_FIELD_INPUT_METHOD_NONE)
,m_length(0)
{
}

Field::~Field(void)
{
}


void Field::setName(const sstring& name)
{
	m_name = name;
}

void Field::setType(EFiledType type)
{
	m_type = type;
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
	if (m_default_value== "now")
	{
		time_t now = time(NULL);
		char buf[64];
		bzero(buf, sizeof(buf));
		snprintf(buf, sizeof(buf), "%ld", now);
		return buf;
	}
	return m_default_value;

}

sstring Field::tip() const
{
	return m_tip;
}

int64_t Field::minValue() const
{
	int64_t min;

	switch(length())
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

	switch(length())
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
	switch(type())
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
	default:
		break;
	}

	return icon;
}


sstring Field::typeString() const
{
	return m_type_string;
}