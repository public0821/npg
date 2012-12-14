#ifndef CONVERTER_DIALOG_H
#define CONVERTER_DIALOG_H

#include <QDialog>
#include "ui/ui_converter_dialog.h"
#include "tools/converter.h"

class ConverterDialog : public QDialog
{
	Q_OBJECT

public:
	ConverterDialog(EConverterType type, const QIcon& icon, QWidget *parent = 0);
	~ConverterDialog();
private slots:
	void onConvert();
	void onRevert();
private:
	Ui::ConverterDialog ui;
	Converter* m_converter;
};

#endif // CONVERTER_DIALOG_H
