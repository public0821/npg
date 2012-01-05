/*
 * category.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef __PROTOCOL_CATEGORY_H__
#define __PROTOCOL_CATEGORY_H__

#include "field.h"
#include <vector>

class Category
{
public:
	Category(bool empty=false);
	~Category(void);
public:
	void addField(const Field& field);
	const std::vector<Field>& fields()const;
	std::vector<Field> optionalFields()const;
	Field field(sstring name)const;
	
	sstring name() const;
	bool isMany() const;
	sstring text() const;
	sstring tip() const;
	void setName(const sstring& name);
	void setMany(bool is_many);
	void setText(const sstring& text);
	void setTip(const sstring& tip);

	bool empty()const;
	u_int16_t optionalFieldCount()const;

private:
	std::vector<Field> m_fields;
	sstring m_name;
	sstring m_text;
	bool m_is_many;
	sstring m_tip;
	bool m_empty;

};
#endif
