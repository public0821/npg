#include "category.h"

Category::Category(bool empty)
:m_is_many(false),m_empty(empty)
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
	if(m_text.empty())
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