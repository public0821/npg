#include "protocol.h"

Protocol::Protocol(bool empty)
:m_empty(empty)
{

}

Protocol::~Protocol(void)
{
}

void Protocol::addCategory(const Category& category)
{
	m_categorys.push_back(category);
}

const std::vector<Category>& Protocol::categorys()const 
{
	return m_categorys;
}

sstring Protocol::name() const
{
	return m_name;
}

sstring Protocol::dependence() const
{
	return m_dependence;
}

sstring Protocol::icon() const
{
	if (m_icon.empty())
	{
		return ":/npg/protocol_udp";
	}
	return m_icon;
}

void Protocol::setName(const sstring& name)
{
	m_name = name;
}

void Protocol::setDependence(const sstring& dependence)
{
	m_dependence = dependence;
}

void Protocol::setIcon(const sstring& icon)
{
	m_icon = icon;
}

bool Protocol::empty()const
{
	return m_empty;
}

Category  Protocol::category(const sstring& name)const 
{
	std::vector<Category>::const_iterator it;
	for (it = m_categorys.begin(); it != m_categorys.end(); ++it)
	{
		if (it->name() == name)
		{
			return *it;
		}
	}

	return Category(true);
}