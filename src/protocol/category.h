#ifndef __PROTOCOL_CATEGORY_H__
#define __PROTOCOL_CATEGORY_H__

#include "field.h"
#include <vector>

class Category
{
public:
	Category(void);
	~Category(void);
public:
	void addField(const Field& field);
	std::vector<Field>& fields();
	
	sstring name() const;
	bool isMany() const;
	sstring text() const;
	void setName(const sstring& name);
	void setMany(bool is_many);
	void setText(const sstring& text);

private:
	std::vector<Field> m_fields;
	sstring m_name;
	sstring m_text;
	bool m_is_many;

};
#endif