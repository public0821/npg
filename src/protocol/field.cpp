#include "field.h"

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
	m_text = m_text;
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
	return m_default_value;

}
sstring Field::tip() const
{
	return m_tip;
}