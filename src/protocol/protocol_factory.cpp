#include "protocol_factory.h"
#include <QDomDocument>
#include <QFile>

ProtocolFactory::ProtocolFactory(void)
{
}

ProtocolFactory::~ProtocolFactory(void)
{
}

ProtocolFactory& ProtocolFactory::instance()
{
	static ProtocolFactory obj;
	obj.loadXml();
	return obj;
}

const std::vector<Protocol>& ProtocolFactory::protocols() const
{
	return m_protocols;
}

Protocol ProtocolFactory::protocol(sstring name)
{
	std::vector<Protocol>::iterator it;
	for (it = m_protocols.begin(); it != m_protocols.end(); ++it)
	{
		if (it->name() == name)
		{
			return *it;
		}
	}

	SET_ERROR_STR("can't find protocol");

	return Protocol(true);
}

void ProtocolFactory::loadXml()
{
	static bool initialized = false;
	if (initialized)
	{
		return;
	}

	QFile file("./conf/ngp.xml");
	if (!file.open(QFile::ReadOnly | QFile::Text)) 
	{
		SET_ERROR_STR(file.errorString().toStdString().c_str());
		return;
	}


	QDomDocument document;
	QString error_str;
	int error_line;
	int error_column;
	if (!document.setContent(&file, true, &error_str, &error_line, &error_column)) 
	{
				SET_ERROR_STR(QString("Parse npg.xml error at line %1, column %2:\n%3")
				.arg(error_line)
				.arg(error_column)
				.arg(error_str).toStdString().c_str());
			return;
	}

	QDomElement root_element = document.documentElement();
	if (root_element.tagName() != "Npg") 
	{
		SET_ERROR_STR("The file npg.xml is not an npg file.");
		return;
	}

	QDomElement protocols_element = root_element.firstChildElement("Protocols");
	if (protocols_element.isNull()) 
	{
		return;
	}

	QDomElement protocol_element = protocols_element.firstChildElement("Protocol");
	while(!protocol_element.isNull())
	{
		loadProtocolElement(&protocol_element);
		protocol_element = protocol_element.nextSiblingElement("Protocol");
	}

	initialized = true;
}

void ProtocolFactory::loadProtocolElement(QDomElement* element)
{
	QDomElement& protocol_element = *element;

	Protocol protocol;
	protocol.setName(protocol_element.attribute("Name", "Unknown").toStdString());
	protocol.setIcon(protocol_element.attribute("Icon").toStdString());
	protocol.setDependence(protocol_element.attribute("Dependence").toStdString());

	QDomElement category_element = protocol_element.firstChildElement("Category");
	while(!category_element.isNull())
	{
		protocol.addCategory(loadCategoryElement(&category_element));
		category_element = category_element.nextSiblingElement("Category");	
	}

	m_protocols.push_back(protocol);
}

Category ProtocolFactory::loadCategoryElement(QDomElement* element)
{
	QDomElement& category_element = *element;

	Category category;
	category.setName(category_element.attribute("Name", "Unknown").toStdString());
	sstring many_str = category_element.attribute("Many").toStdString();
	if (many_str == "true")
	{
		category.setMany(true);
	}
	category.setText(category_element.attribute("Text").toStdString());
	category.setTip(category_element.attribute("Tip").toStdString());

	QDomElement field_element = category_element.firstChildElement("Field");
	while(!field_element.isNull())
	{
		category.addField(loadFieldElement(&field_element));
		field_element = field_element.nextSiblingElement("Field");	
	}

	return category;
}

Field ProtocolFactory::loadFieldElement(QDomElement* element)
{
	QDomElement& field_element = *element;

	Field field;
	field.setName(field_element.attribute("Name", "Unknown").toStdString());

	sstring type_str = field_element.attribute("Type").toStdString();
	if (type_str == "int")
	{
		field.setType(E_FIELD_TYPE_INT);
	}
	else if (type_str == "ip")
	{
		field.setType(E_FIELD_TYPE_IP);
	}
	else if (type_str == "string")
	{
		field.setType(E_FIELD_TYPE_STRING);
	}
	else
	{
		SET_ERROR_STR((sstring("Unknown field type:")+type_str).c_str());
	}

	sstring input_method_str = field_element.attribute("InputMethod").toStdString();
	if (input_method_str == "edit")
	{
		field.setInputMethod(E_FIELD_INPUT_METHOD_EDIT);
	}
	else if (input_method_str == "none")
	{
		field.setInputMethod(E_FIELD_INPUT_METHOD_NONE);
	}
	else if (input_method_str == "select")
	{
		field.setInputMethod(E_FIELD_INPUT_METHOD_SELECT);
	}
	else
	{
		SET_ERROR_STR((sstring("Unknown field input method:")+type_str).c_str());
	}

	field.setLength(field_element.attribute("Length").toInt());
	field.setText(field_element.attribute("Text").toStdString());
	field.setDefaultValue(field_element.attribute("DefaultValue").toStdString());
	field.setTip(field_element.attribute("Tip").toStdString());

	return field;
}