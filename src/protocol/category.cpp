#include "category.h"

Category::Category(bool empty) :
		m_is_many(false), m_empty(empty)
{
}

Category::~Category(void)
{
}

void Category::addField(const Field& field)
{
	m_fields.push_back(field);
}

const std::vector<Field>& Category::fields() const
{
	return m_fields;
}

Field Category::field(sstring name) const
{
	std::vector<Field>::const_iterator it;
	for (it = m_fields.begin(); it != m_fields.end(); ++it)
	{
		if (it->name() == name)
		{
			return *it;
		}
	}

	return Field(true);
}

std::vector<Field> Category::optionalFields() const
{
	std::vector<Field> optional_fields;
	std::vector<Field>::const_iterator it;
	for (it = m_fields.begin(); it != m_fields.end(); ++it)
	{
		if (it->isOptional())
		{
			optional_fields.push_back(*it);
		}
	}

	return optional_fields;
}

sstring Category::name() const
{
	return m_name;
}

bool Category::isMany() const
{
	return m_is_many;
}

sstring Category::text() const
{
	if (m_text.empty())
	{
		return m_name;
	}

	return m_text;
}

void Category::setName(const sstring& name)
{
	m_name = name;
}

void Category::setMany(bool is_many)
{
	m_is_many = is_many;
}

void Category::setText(const sstring& text)
{
	m_text = text;
}

sstring Category::tip() const
{
	return m_tip;
}

void Category::setTip(const sstring& tip)
{
	m_tip = tip;
}

u_int16_t Category::optionalFieldCount() const
{
	u_int16_t count = 0;
	std::vector<Field>::const_iterator it;
	for (it = m_fields.begin(); it != m_fields.end(); ++it)
	{
		if (it->isOptional())
		{
			count++;
		}
	}

	return count;
}
