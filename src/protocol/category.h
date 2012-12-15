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
	Field field(QString name)const;
	
	QString name() const;
	bool isMany() const;
	QString text() const;
	QString tip() const;
	QString tail()const;
	QString prefix()const;


	void setName(const QString& name);
	void setMany(bool is_many);
	void setText(const QString& text);
	void setTip(const QString& tip);
	void setTail(const QString& tail);
	void setPrefix(const QString& prefix);

	bool empty()const;
	uint16_t optionalFieldCount()const;

private:
	std::vector<Field> m_fields;
	QString m_name;
	QString m_text;
	bool m_is_many;
	QString m_tip;
	bool m_empty;
	QString m_tail;
	QString m_prefix;

};
#endif
