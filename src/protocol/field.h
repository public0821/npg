#ifndef __PROTOCOL_FIELD_H__
#define __PROTOCOL_FIELD_H__

#include "system/types.h"


enum EFiledType
{
	E_FIELD_TYPE_INT = 1
	, E_FIELD_TYPE_STRING
	, E_FIELD_TYPE_IP
	, E_FIELD_TYPE_BIT
};

enum EFiledInputMethod
{
	E_FIELD_INPUT_METHOD_NONE = 0
	, E_FIELD_INPUT_METHOD_LINEEDIT
	, E_FIELD_INPUT_METHOD_TEXTEDIT
	, E_FIELD_INPUT_METHOD_SELECT
};


class Field
{
public:
	Field(bool empty=false);
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

	sstring name() const;
	EFiledType type() const;
	sstring typeString() const;
	EFiledInputMethod inputMethod() const;
	size_t length() const;
	sstring text() const;
	sstring tip() const;
	sstring defaultValue() const;
	int64_t minValue() const;
	u_int64_t maxValue() const;
	sstring icon()const;
	bool isOptional()const;

	bool empty()const;
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
	//int64_t m_min;
	//u_int64_t m_max;
	
};

#endif