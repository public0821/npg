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
	
	sstring name() const;
	bool isMany() const;
	sstring text() const;
	sstring tip() const;
	void setName(const sstring& name);
	void setMany(bool is_many);
	void setText(const sstring& text);
	void setTip(const sstring& tip);

	bool empty()const;

private:
	std::vector<Field> m_fields;
	sstring m_name;
	sstring m_text;
	bool m_is_many;
	sstring m_tip;
	bool m_empty;

};
#endif