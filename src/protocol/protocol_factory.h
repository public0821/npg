/*
 * protocol_factory.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_FACTORY_H__
#define __PROTOCOL_FACTORY_H__

#include "protocol.h"

class QDomElement;
class ProtocolFactory
{
private:
	ProtocolFactory(void);
public:
	~ProtocolFactory(void);

public:
	static ProtocolFactory& instance();
	bool loadXml();
public:
	const std::vector<Protocol>& protocols() const;
	Protocol protocol(QString name);
private:
	void loadProtocolElement(QDomElement* element, bool need_show);
	Category loadCategoryElement(QDomElement* element);
	Field loadFieldElement(const QString& category_name, QDomElement* element);
	bool loadProtocolXml(const QString& file_name);
	bool loadNpgXml(const QString& file_name);
	bool rebuildAllProtocol();
	bool rebuildProtocol(Protocol& protocol);

private:
	std::vector<Protocol> m_protocols;
//	std::vector<Protocol> m_protocols_hide;
};
#endif
