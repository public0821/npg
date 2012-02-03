/*
 * protocol_factory.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_FACTORY_H__
#define __PROTOCOL_FACTORY_H__

#include "protocol.h"
#include "system/qerror.h"

class QDomElement;
class ProtocolFactory : public QError
{
private:
	ProtocolFactory(void);
public:
	~ProtocolFactory(void);

public:
	static ProtocolFactory& instance();
public:
	const std::vector<Protocol>& protocols() const;
	Protocol protocol(QString name);
private:
	void loadXml();
	void loadProtocolElement(QDomElement* element);
	Category loadCategoryElement(QDomElement* element);
	Field loadFieldElement(const QString& category_name, QDomElement* element);

private:
	std::vector<Protocol> m_protocols;
};
#endif