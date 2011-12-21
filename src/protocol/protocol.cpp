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

EBaseProtocol Protocol::dependence() const
{
	return m_dependence;
}

sstring Protocol::DependenceParam()const
{
	return m_dependence_param;
}
sstring Protocol::dependenceString() const
{
	return m_dependence_string;
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

void Protocol::setDependence(EBaseProtocol dependence)
{
	m_dependence = dependence;
}

void Protocol::setDependenceString(const sstring& dependence)
{
	m_dependence_string = dependence;
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

void Protocol::setDependenceParam(const sstring& dependence_param)
{
	m_dependence_param = dependence_param;
}