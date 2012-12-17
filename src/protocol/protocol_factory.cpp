#include "protocol_factory.h"
#include <QDomDocument>
#include <QFile>
#include <QLocale>
#include "npg_define.h"
#include "../logger.h"

ProtocolFactory::ProtocolFactory(void)
{
}

ProtocolFactory::~ProtocolFactory(void)
{
}

ProtocolFactory& ProtocolFactory::instance()
{
	static ProtocolFactory obj;
	return obj;
}

const std::vector<Protocol>& ProtocolFactory::protocols() const
{
	return m_protocols;
}

Protocol ProtocolFactory::protocol(QString name)
{
	std::vector<Protocol>::iterator it;
	for (it = m_protocols.begin(); it != m_protocols.end(); ++it)
	{
		if (it->name() == name)
		{
			return *it;
		}
	}

	LOG_ERROR(QObject::tr("can't find protocol:%1").arg(name));

	return Protocol(true);
}

bool ProtocolFactory::loadXml()
{
	static bool initialized = false;
	if (initialized)
	{
		return true;
	}

	QString file_name = "./conf/npg_" + QLocale::system().name() + ".xml";
	QFile file(file_name);
	if (!file.open(QFile::ReadOnly | QFile::Text)) 
	{
		file.close();
		file_name = "./conf/npg.xml";
		file.setFileName(file_name);
		if (!file.open(QFile::ReadOnly | QFile::Text)) 
		{
			LOG_ERROR(QObject::tr("Open config file fail:") + file.errorString());
			return false;
		}
	}

	QDomDocument document;
	QString error_str;
	int error_line;
	int error_column;
	if (!document.setContent(&file, true, &error_str, &error_line, &error_column)) 
	{
		LOG_ERROR(QObject::tr("Parse %1 error at line %2, column %3:\n%4")
				.arg(file_name)
				.arg(error_line)
				.arg(error_column)
				.arg(error_str));
			return false;
	}

	QDomElement root_element = document.documentElement();
	if (root_element.tagName() != "Npg") 
	{
		LOG_ERROR(QObject::tr("The file %1 is not an npg file.").arg(file_name));
		return false;
	}

	QDomElement protocols_element = root_element.firstChildElement("Protocols");
	if (protocols_element.isNull()) 
	{
		return false;
	}

	QDomElement protocol_element = protocols_element.firstChildElement("Protocol");
	while(!protocol_element.isNull())
	{
		loadProtocolElement(&protocol_element);
		protocol_element = protocol_element.nextSiblingElement("Protocol");
	}

	initialized = true;

	return true;
}

void ProtocolFactory::loadProtocolElement(QDomElement* element)
{
	QDomElement& protocol_element = *element;

	Protocol protocol;
	protocol.setName(protocol_element.attribute("Name", "Unknown"));
	protocol.setIcon(protocol_element.attribute("Icon"));
	protocol.setDependenceParam(protocol_element.attribute("DependenceParam"));
	QString dependence_str = protocol_element.attribute("Dependence");
	protocol.setDependenceString(dependence_str);
	if (dependence_str == K_PROTOCOL_UDP)
	{
		protocol.setDependence(E_BASE_PROTOCOL_UDP);
	}
	else if (dependence_str == K_PROTOCOL_TCP)
	{
		protocol.setDependence(E_BASE_PROTOCOL_TCP);
	}
	else  if (dependence_str == K_PROTOCOL_IP)
	{
		protocol.setDependence(E_BASE_PROTOCOL_IP);
	}
	else  if (dependence_str == K_PROTOCOL_ETHERNET)
	{
		protocol.setDependence(E_BASE_PROTOCOL_ETHERNET);
	}
	else
	{
		LOG_ERROR(QObject::tr("Unknown Dependence Protocol:%1").arg(dependence_str));
	}
	

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
	category.setName(category_element.attribute("Name", "Unknown"));
	QString many_str = category_element.attribute("Many");
	if (many_str == "true")
	{
		category.setMany(true);
	}
	category.setText(category_element.attribute("Text"));
	category.setTip(category_element.attribute("Tip"));
	category.setTail(category_element.attribute("Tail"));
	category.setPrefix(category_element.attribute("Prefix"));

	QDomElement field_element = category_element.firstChildElement("Field");
	while(!field_element.isNull())
	{
		category.addField(loadFieldElement(category.name(), &field_element));
		field_element = field_element.nextSiblingElement("Field");	
	}

	return category;
}

Field ProtocolFactory::loadFieldElement(const QString& category_name, QDomElement* element)
{
	QDomElement& field_element = *element;

	Field field(category_name);
	field.setName(field_element.attribute("Name", "Unknown"));

	QString type_str = field_element.attribute("Type");
	field.setTypeString(type_str);
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
	else if (type_str == "mac")
	{
		field.setType(E_FIELD_TYPE_MAC);
	}
	else if (type_str == "bit")
	{
		field.setType(E_FIELD_TYPE_BIT);
	}
	else
	{
		LOG_ERROR(QObject::tr("Unknown field type:%1").arg(type_str));
	}

	QString input_method_str = field_element.attribute("InputMethod");
	if (input_method_str == "lineedit")
	{
		field.setInputMethod(E_FIELD_INPUT_METHOD_LINEEDIT);
	}
	else if (input_method_str == "textedit")
	{
		field.setInputMethod(E_FIELD_INPUT_METHOD_TEXTEDIT);
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
		LOG_ERROR(QObject::tr("Unknown field input method:%1").arg(input_method_str));
	}

	field.setLength(field_element.attribute("Length").toInt());
	field.setText(field_element.attribute("Text"));
	field.setDefaultValue(field_element.attribute("DefaultValue"));
	field.setTip(field_element.attribute("Tip"));
	field.setTail(field_element.attribute("Tail"));
	field.setPrefix(field_element.attribute("Prefix"));

	QString optional_str = field_element.attribute("Optional");
	if (optional_str == "true")
	{
		field.setOptional(true);
	}
	else
	{
		field.setOptional(false);
	}

	QString editable_str = field_element.attribute("Editable");
	if (editable_str == "false")
	{
		field.setEditable(false);
	}
	else
	{
		field.setEditable(true);
	}

	QString show_on_start_str = field_element.attribute("ShowOnStart");
	if (show_on_start_str == "true")
	{
		field.setShowOnStart(true);
	}
	else
	{
		field.setShowOnStart(false);
	}

	QDomElement item_element = field_element.firstChildElement("Item");
	while(!item_element.isNull())
	{
		FieldItem field_item;
		field_item.setText(item_element.attribute("Text"));
		field_item.setValue(item_element.attribute("Value"));
		item_element = item_element.nextSiblingElement("Item");	
		field.addItem(field_item);
	}

	QDomElement subfield_element = field_element.firstChildElement("SubField");
	while(!subfield_element.isNull())
	{
		field.addSubField(loadFieldElement(category_name, &subfield_element));
		subfield_element = subfield_element.nextSiblingElement("SubField");	
	}

	return field;
}
