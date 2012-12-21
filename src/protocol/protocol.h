/*
 * protocol.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "category.h"

enum EBaseProtocol
{
	E_BASE_PROTOCOL_UNKNOWN = 0
	, E_BASE_PROTOCOL_UDP
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
	Category  category(const QString& name)const ;
public:
	QString name() const;
	EBaseProtocol dependence() const;
	QString dependenceString() const;
	QString dependenceParam()const;
	QString icon() const;
	bool needShow()const ;

	void setName(const QString& name);
	void setDependenceString(const QString& dependence);
	void setDependence(EBaseProtocol dependence);
	void setDependenceParam(const QString& dependence_param);
	void setIcon(const QString& icon);
	void setNeedShow(bool need_show);

	bool empty()const;

private:
	std::vector<Category> m_categorys;
private:
	QString m_name;
	EBaseProtocol m_dependence;
	QString m_dependence_string;
	QString m_icon;
	bool m_empty;
	QString m_dependence_param;
	bool m_need_show;

	friend class ProtocolFactory;
};
#endif
