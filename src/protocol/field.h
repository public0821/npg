#ifndef __PROTOCOL_FIELD_H__
#define __PROTOCOL_FIELD_H__

#include "system/types.h"


enum EFiledType
{
	E_FIELD_TYPE_INT = 1
	, E_FIELD_TYPE_STRING
	, E_FIELD_TYPE_IP
};

enum EFiledInputMethod
{
	E_FIELD_INPUT_METHOD_NONE = 0
	, E_FIELD_INPUT_METHOD_EDIT
	, E_FIELD_INPUT_METHOD_SELECT
};


class Field
{
public:
	Field(void);
	~Field(void);
public:
	void setName(const sstring& name);
	void setType(EFiledType type);
	void setInputMethod(EFiledInputMethod input_method);
	void setLength(size_t length);
	void setText(const sstring& text);
	void setTip(const sstring& tip);
	void setDefaultValue(const sstring& default_value);

	sstring name() const;
	EFiledType type() const;
	EFiledInputMethod inputMethod() const;
	size_t length() const;
	sstring text() const;
	sstring tip() const;
	sstring defaultValue() const;
private:
	sstring m_name;
	EFiledType m_type;
	EFiledInputMethod m_input_method;
	size_t m_length;
	sstring m_text;
	sstring m_default_value;
	sstring m_tip;
	
};

#endif