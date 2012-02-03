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

QString Protocol::name() const
{
	return m_name;
}

EBaseProtocol Protocol::dependence() const
{
	return m_dependence;
}

QString Protocol::DependenceParam()const
{
	return m_dependence_param;
}
QString Protocol::dependenceString() const
{
	return m_dependence_string;
}

QString Protocol::icon() const
{
	if (m_icon.isEmpty())
	{
		return ":/npg/protocol_default";
	}
	return m_icon;
}

void Protocol::setName(const QString& name)
{
	m_name = name;
}

void Protocol::setDependence(EBaseProtocol dependence)
{
	m_dependence = dependence;
}

void Protocol::setDependenceString(const QString& dependence)
{
	m_dependence_string = dependence;
}

void Protocol::setIcon(const QString& icon)
{
	m_icon = icon;
}

bool Protocol::empty()const
{
	return m_empty;
}

Category  Protocol::category(const QString& name)const 
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

void Protocol::setDependenceParam(const QString& dependence_param)
{
	m_dependence_param = dependence_param;
}