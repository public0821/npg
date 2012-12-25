/*
 * field.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_FIELD_H__
#define __PROTOCOL_FIELD_H__

#include "lib/types.h"
#include <vector>
#include <QString>


enum EFiledType
{
	E_FIELD_TYPE_INT = 1
	, E_FIELD_TYPE_STRING
	, E_FIELD_TYPE_IP
	, E_FIELD_TYPE_BIT
	, E_FIELD_TYPE_MAC
};

//enum EFiledInputMethod
//{
//	E_FIELD_INPUT_METHOD_NONE = 0
//	, E_FIELD_INPUT_METHOD_LINEEDIT
//	, E_FIELD_INPUT_METHOD_TEXTEDIT
//	, E_FIELD_INPUT_METHOD_SELECT
//};

const char K_DEFAULT_VALUE_SECOND[] = "second";
const char K_DEFAULT_VALUE_PID[] = "pid";
const char K_DEFAULT_VALUE_MILLISECOND[] = "millisecond";
const char K_DEFAULT_VALUE_CHECKNUM[] = "checksum";
const char K_DEFAULT_VALUE_SEQ[] = "seq";

class FieldItem
{
public:
	QString text()const{return m_name;};
	QString value()const{return m_value;};
	void setText(const QString& name){m_name = name;};
	void setValue(const QString& value){m_value = value;};
private:
	QString m_name;
	QString m_value;
};

class Field
{
public:
	Field(const QString& category_name, bool empty=false);
	~Field(void);
public:
	void setName(const QString& name);
	void setType(EFiledType type);
	void setTypeString(QString type_string);
//	void setInputMethod(EFiledInputMethod input_method);
	void setLength(size_t length);
	void setText(const QString& text);
	void setTip(const QString& tip);
	void setDefaultValue(const QString& default_value);
	void setOptional(bool optional);
	void addItem(const FieldItem& item);
	void setEditable(bool editable);
	void setShowOnStart(bool show_on_start);
	void addSubField(const Field& sub_field);
	void setSuffix(const QString& suffix);
	void setPrefix(const QString& prefix);

	QString name() const;
	EFiledType type() const;
	QString typeString() const;
//	EFiledInputMethod inputMethod() const;
	size_t length() const;
	QString text() const;
	QString tip() const;
	QString defaultValue() const;
	QString defaultValueOriginal() const;
	int64_t minValue() const;
	uint64_t maxValue() const;
	QString icon()const;
	bool isOptional()const;
	bool empty()const;
	const std::vector<FieldItem>& items()const;
	bool isItemsEmpty()const;
	bool editable()const;
	QString categoryName()const;
	bool isShowOnStart()const;
	const std::vector<Field>& subFields()const;
	bool isSubFieldsEmpty()const ;
	Field subField(const QString& sub_field_name)const;
	QString suffix()const;
	QString prefix()const;

	void clear();
private:
	QString m_name;
	EFiledType m_type;
//	EFiledInputMethod m_input_method;
	size_t m_length;
	QString m_text;
	QString m_default_value;
	QString m_tip;
	QString m_type_string;
	bool m_empty;
	bool m_optional;
	std::vector<FieldItem> m_items;
	bool m_editable;
	QString m_category_name;
	bool m_show_on_start;
	std::vector<Field> m_sub_fields;
	QString m_suffix;
	QString m_prefix;
};

#endif
