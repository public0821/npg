#ifndef __PROTOCOL_FACTORY_H__
#define __PROTOCOL_FACTORY_H__

#include "protocol.h"
#include "system/error.h"

class QDomElement;
class ProtocolFactory : public Error
{
private:
	ProtocolFactory(void);
public:
	~ProtocolFactory(void);

public:
	static ProtocolFactory& instance();
public:
	const std::vector<Protocol>& protocols() const;
	Protocol protocol(sstring name);
private:
	void loadXml();
	void loadProtocolElement(QDomElement* element);
	Category loadCategoryElement(QDomElement* element);
	Field loadFieldElement(const sstring& category_name, QDomElement* element);

private:
	std::vector<Protocol> m_protocols;
};
#endif