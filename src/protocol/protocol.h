#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "category.h"

enum EBaseProtocol
{
	E_BASE_PROTOCOL_UDP = 0
	, E_BASE_PROTOCOL_TCP
	, E_BASE_PROTOCOL_IP
	,E_BASE_PROTOCOL_ETHERNET
};


class Protocol
{
public:
	Protocol(bool empty = false);
	~Protocol(void);
public:
	void addCategory(const Category& category);
	const  std::vector<Category>& categorys()const ;
	Category  category(const sstring& name)const ;
public:
	sstring name() const;
	EBaseProtocol dependence() const;
	sstring dependenceString() const;
	sstring DependenceParam()const;
	sstring icon() const;

	void setName(const sstring& name);
	void setDependenceString(const sstring& dependence);
	void setDependence(EBaseProtocol dependence);
	void setDependenceParam(const sstring& dependence_param);
	void setIcon(const sstring& icon);

	bool empty()const;

private:
	std::vector<Category> m_categorys;
private:
	sstring m_name;
	EBaseProtocol m_dependence;
	sstring m_dependence_string;
	sstring m_icon;
	bool m_empty;
	sstring m_dependence_param;
};
#endif