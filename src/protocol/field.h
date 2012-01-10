/*
 * field.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_FIELD_H__
#define __PROTOCOL_FIELD_H__

#include "system/types.h"
#include <vector>


enum EFiledType
{
	E_FIELD_TYPE_INT = 1
	, E_FIELD_TYPE_STRING
	, E_FIELD_TYPE_IP
	, E_FIELD_TYPE_BIT
	, E_FIELD_TYPE_MAC
};

enum EFiledInputMethod
{
	E_FIELD_INPUT_METHOD_NONE = 0
	, E_FIELD_INPUT_METHOD_LINEEDIT
	, E_FIELD_INPUT_METHOD_TEXTEDIT
	, E_FIELD_INPUT_METHOD_SELECT
};

const char K_DEFAULT_VALUE_SECOND[] = "second";
const char K_DEFAULT_VALUE_PID[] = "pid";
const char K_DEFAULT_VALUE_MILLISECOND[] = "millisecond";
const char K_DEFAULT_VALUE_CHECKNUM[] = "checknum";
const char K_DEFAULT_VALUE_SEQ[] = "seq";

const char K_DEFAULT_VALUE_DEFAULT[] = "default";

class FieldItem
{
public:
	sstring text()const{return m_name;};
	sstring value()const{return m_value;};
	void setText(const sstring& name){m_name = name;};
	void setValue(const sstring& value){m_value = value;};
private:
	sstring m_name;
	sstring m_value;
};

class Field
{
public:
	Field(const sstring& category_name, bool empty=false);
	~Field(void);
public:
	void setName(const sstring& name);
	void setType(EFiledType type);
	void setTypeString(sstring type_string);
	void setInputMethod(EFiledInputMethod input_method);
	void setLength(size_t length);
	void setText(const sstring& text);
	void setTip(const sstring& tip);
	void setDefaultValue(const sstring& default_value);
	void setOptional(bool optional);
	void addItem(const FieldItem& item);
	void setEditable(bool editable);
	void setShowOnStart(bool show_on_start);
	void addSubField(const Field& sub_field);
	void setTail(const sstring& tail);
	void setPrefix(const sstring& prefix);

	sstring name() const;
	EFiledType type() const;
	sstring typeString() const;
	EFiledInputMethod inputMethod() const;
	size_t length() const;
	sstring text() const;
	sstring tip() const;
	sstring defaultValue() const;
	sstring defaultValueOriginal() const;
	int64_t minValue() const;
	u_int64_t maxValue() const;
	sstring icon()const;
	bool isOptional()const;
	bool empty()const;
	const std::vector<FieldItem>& items()const;
	bool editable()const;
	sstring categoryName()const;
	bool isShowOnStart()const;
	const std::vector<Field>& subFields()const;
	Field subField(const sstring& sub_field_name)const;
	sstring tail()const;
	sstring prefix()const;
private:
	sstring m_name;
	EFiledType m_type;
	EFiledInputMethod m_input_method;
	size_t m_length;
	sstring m_text;
	sstring m_default_value;
	sstring m_tip;
	sstring m_type_string;
	bool m_empty;
	bool m_optional;
	std::vector<FieldItem> m_items;
	bool m_editable;
	sstring m_category_name;
	bool m_show_on_start;
	std::vector<Field> m_sub_fields;
	sstring m_tail;
	sstring m_prefix;
};

#endif