#include "protocol_factory.h"
#include <QDomDocument>
#include <QFile>
#include <QLocale>
#include "config.h"
#include "../logger.h"
#include <qdir.h>

ProtocolFactory::ProtocolFactory(void) {
}

ProtocolFactory::~ProtocolFactory(void) {
}

ProtocolFactory& ProtocolFactory::instance() {
	static ProtocolFactory obj;
	return obj;
}

const std::vector<Protocol>& ProtocolFactory::protocols() const {
	return m_protocols;
}

Protocol ProtocolFactory::protocol(QString name) {
	std::vector<Protocol>::iterator it;
	for (it = m_protocols.begin(); it != m_protocols.end(); ++it) {
		if (it->name() == name) {
			return *it;
		}
	}

	LOG_ERROR(QObject::tr("can't find protocol:%1").arg(name));

	return Protocol(true);
}

bool ProtocolFactory::loadProtocolXml(const QString& file_name) {
	QFile file(file_name);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		LOG_ERROR(QObject::tr("Open config file  %1 fail: %2").arg(file_name).arg(file.errorString()));
		return false;
	}

	QDomDocument document;
	QString error_str;
	int error_line;
	int error_column;
	if (!document.setContent(&file, true, &error_str, &error_line, &error_column)) {
		LOG_ERROR(QObject::tr("Parse %1 error at line %2, column %3:\n%4")
				.arg(file_name)
				.arg(error_line)
				.arg(error_column)
				.arg(error_str));
		return false;
	}

	QDomElement protocols_element = document.documentElement();
	if (protocols_element.isNull() || protocols_element.tagName() != "Protocols") {
		LOG_ERROR(QObject::tr("The file %1 is not an npg file.").arg(file_name));
		return false;
	}

	QDomElement protocol_element = protocols_element.firstChildElement("Protocol");
	while (!protocol_element.isNull())
	{
		loadProtocolElement(&protocol_element, true);
		protocol_element = protocol_element.nextSiblingElement("Protocol");
	}

	return true;
}

bool ProtocolFactory::loadNpgXml(const QString& file_name) {
	QFile file(file_name);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		LOG_ERROR(QObject::tr("Open config file fail:") + file.errorString());
		return false;
	}

	QDomDocument document;
	QString error_str;
	int error_line;
	int error_column;
	if (!document.setContent(&file, true, &error_str, &error_line, &error_column)) {
		LOG_ERROR(QObject::tr("Parse %1 error at line %2, column %3:\n%4")
				.arg(file_name)
				.arg(error_line)
				.arg(error_column)
				.arg(error_str));
		return false;
	}

	QDomElement root_element = document.documentElement();
	if (root_element.tagName() != "Npg") {
		LOG_ERROR(QObject::tr("The file %1 is not an npg file.").arg(file_name));
		return false;
	}

	QDomElement protocols_element = root_element.firstChildElement("Protocols");
	if (protocols_element.isNull()) {
		return false;
	}

	QDomElement protocol_element = protocols_element.firstChildElement("Protocol");
	while (!protocol_element.isNull()) {
		loadProtocolElement(&protocol_element, false);
		protocol_element = protocol_element.nextSiblingElement("Protocol");
	}
	return true;
}

bool ProtocolFactory::rebuildProtocol(Protocol& protocol) {
	std::vector<Category> new_categorys;
	for (size_t i = 0; i < protocol.m_categorys.size(); i++) {
		QString ref = protocol.m_categorys[i].refProtocol();
		if (ref.length() == 0) {
			new_categorys.push_back(protocol.m_categorys[i]);
			continue;
		}
		Protocol ref_protocol = this->protocol(ref);
		if(ref_protocol.empty()){
			continue;
		}
		rebuildProtocol(ref_protocol);

		for (size_t j = 0; j < ref_protocol.m_categorys.size(); j++) {
			new_categorys.push_back(ref_protocol.m_categorys[j]);
		}
	}

	protocol.m_categorys = new_categorys;

	return true;
}

bool ProtocolFactory::rebuildAllProtocol() {
	for (size_t i = 0; i < m_protocols.size(); i++) {
		rebuildProtocol(m_protocols[i]);
	}

	return true;
}

bool ProtocolFactory::loadXml()
{
	static bool initialized = false;
	if (initialized) {
		return true;
	}
	QString conf_file_path = "./conf/" + QLocale::system().name() + "/";
//	LOG_TRACE(conf_file_path);
	if (!QDir(conf_file_path).exists()) {
		conf_file_path = "./conf/";
	}
//	LOG_TRACE(conf_file_path);
	//load all protocols
	QDir conf_dir(conf_file_path);
	QStringList filter;
	filter << "*.xml";
	QStringList file_list = conf_dir.entryList(filter);
	for (int i = 0; i < file_list.count(); i++) {
		QString conf_file = conf_file_path + file_list.at(i);
		if (file_list.at(i) == "npg.xml") {
			continue;
		}
//		LOG_TRACE(conf_file);
		loadProtocolXml(conf_file);
	}

	QString npg_file_name = conf_file_path + "npg.xml";
	loadNpgXml(npg_file_name);

	rebuildAllProtocol();

	initialized = true;

	return true;
}

void ProtocolFactory::loadProtocolElement(QDomElement* element, bool need_show) {
	QDomElement& protocol_element = *element;

	Protocol protocol;
	protocol.setName(protocol_element.attribute("Name", "Unknown"));
	for (size_t i = 0; i < m_protocols.size(); i++) {
		if (m_protocols[i].name() == protocol.name()) {
			LOG_ERROR(QObject::tr("protocol already exist:%1").arg(protocol.name()));
			return;
		}
	}
	protocol.setIcon(protocol_element.attribute("Icon"));
	protocol.setDependenceParam(protocol_element.attribute("DependenceParam"));
	QString dependence_str = protocol_element.attribute("Dependence");
	protocol.setDependenceString(dependence_str);
	if (dependence_str == K_BASE_PROTOCOL_UDP) {
		protocol.setDependence(E_BASE_PROTOCOL_UDP);
	} else if (dependence_str == K_BASE_PROTOCOL_TCP) {
		protocol.setDependence(E_BASE_PROTOCOL_TCP);
	} else if (dependence_str == K_BASE_PROTOCOL_IP) {
		protocol.setDependence(E_BASE_PROTOCOL_IP);
	} else if (dependence_str == K_BASE_PROTOCOL_ETHERNET) {
		protocol.setDependence(E_BASE_PROTOCOL_ETHERNET);
	} else if (dependence_str.length() == 0) {
		protocol.setDependence(E_BASE_PROTOCOL_UNKNOWN);
	} else {
		LOG_ERROR(QObject::tr("'%1' Unknown Dependence Protocol:%2").arg(protocol.name()).arg(dependence_str));
		return;
	}

	QDomElement category_element = protocol_element.firstChildElement("Category");
	while (!category_element.isNull()) {
		Category categoty = loadCategoryElement(&category_element);
		if (categoty.empty()) {
			return;
		}
		protocol.addCategory(categoty);
		category_element = category_element.nextSiblingElement("Category");
	}
	protocol.setNeedShow(need_show);
	m_protocols.push_back(protocol);
}

Category ProtocolFactory::loadCategoryElement(QDomElement* element) {
	QDomElement& category_element = *element;

	Category category;
	category.setName(category_element.attribute("Name", "Unknown"));
	category.setRefProtocol(category_element.attribute("Ref"));
	QString many_str = category_element.attribute("Many");
	if (many_str == "true") {
		category.setMany(true);
	}
	category.setText(category_element.attribute("Text"));
	category.setTip(category_element.attribute("Tip"));
	category.setSuffix(category_element.attribute("Suffix"));
	category.setPrefix(category_element.attribute("Prefix"));

	QDomElement field_element = category_element.firstChildElement("Field");
	while (!field_element.isNull()) {
		Field field = loadFieldElement(category.name(), &field_element);
		if (field.empty()) {
			category.clear();
			return category;
		}
		category.addField(field);
		field_element = field_element.nextSiblingElement("Field");
	}

	return category;
}

Field ProtocolFactory::loadFieldElement(const QString& category_name, QDomElement* element) {
	QDomElement& field_element = *element;

	Field field(category_name);
	field.setName(field_element.attribute("Name", "Unknown"));

	QString type_str = field_element.attribute("Type");
	field.setTypeString(type_str);
	if (type_str == "int") {
		field.setType(E_FIELD_TYPE_INT);
	}
	else if (type_str == "ip") {
		field.setType(E_FIELD_TYPE_IP);
	}
	else if (type_str == "string") {
		field.setType(E_FIELD_TYPE_STRING);
	}
	else if (type_str == "mac") {
		field.setType(E_FIELD_TYPE_MAC);
	}
	else if (type_str == "bit") {
		field.setType(E_FIELD_TYPE_BIT);
	} else {
		LOG_ERROR(QObject::tr("Unknown field type:%1").arg(type_str));
		field.clear();
		return field;
	}

	field.setLength(field_element.attribute("Length").toInt());
	field.setText(field_element.attribute("Text"));
	field.setDefaultValue(field_element.attribute("DefaultValue"));
	field.setTip(field_element.attribute("Tip"));
	field.setSuffix(field_element.attribute("Suffix"));
	field.setPrefix(field_element.attribute("Prefix"));

	QString optional_str = field_element.attribute("Optional");
	if (optional_str == "true") {
		field.setOptional(true);
	} else {
		field.setOptional(false);
	}

	QString editable_str = field_element.attribute("Editable");
	if (editable_str == "false") {
		field.setEditable(false);
	} else {
		field.setEditable(true);
	}

	QString show_on_start_str = field_element.attribute("ShowOnStart");
	if (show_on_start_str == "true") {
		field.setShowOnStart(true);
	} else {
		field.setShowOnStart(false);
	}

	QDomElement item_element = field_element.firstChildElement("Item");
	while (!item_element.isNull()) {
		FieldItem field_item;
		field_item.setText(item_element.attribute("Text"));
		field_item.setValue(item_element.attribute("Value"));
		item_element = item_element.nextSiblingElement("Item");
		field.addItem(field_item);
	}

	QDomElement subfield_element = field_element.firstChildElement("SubField");
	while (!subfield_element.isNull()) {
		Field subfield = loadFieldElement(category_name, &subfield_element);
		if (subfield.empty()) {
			field.clear();
			return field;
		}
		field.addSubField(subfield);
		subfield_element = subfield_element.nextSiblingElement("SubField");
	}

	return field;
}
