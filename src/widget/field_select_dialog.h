#ifndef FIELD_SELECT_DIALOG_H
#define FIELD_SELECT_DIALOG_H

#include <QDialog>
#include "ui_field_select_dialog.h"
#include "protocol/field.h"

class FieldSelectDialog : public QDialog
{
	Q_OBJECT

public:
	FieldSelectDialog(const std::vector<Field>& optional_fields, QWidget *parent = 0);
	~FieldSelectDialog();
public:
	std::vector<Field> selectedFields();
protected slots:
	void onOk();
private:
	Ui::FieldSelectDialog ui;
	std::vector<Field> m_optional_fields;
	bool m_ok;
};

#endif // FIELD_SELECT_DIALOG_H
