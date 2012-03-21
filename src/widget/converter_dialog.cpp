#include "converter_dialog.h"
#include <QMessageBox>

ConverterDialog::ConverterDialog(Converter* converter, QIcon& icon, QWidget *parent)
	:m_converter(converter), QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
	ui.setupUi(this);

	setWindowTitle(converter->title());
	setWindowIcon(icon);

	ui.from_label->setText(converter->fromTextTip());
	ui.to_label->setText(converter->toTextTip());

	connect(ui.convert_button, SIGNAL(released(void)), this, SLOT(onConvert(void)));
	connect(ui.revert_button, SIGNAL(released(void)), this, SLOT(onRevert(void)));
}

ConverterDialog::~ConverterDialog()
{

}


void ConverterDialog::onConvert()
{
	QString text = ui.from_edit->toPlainText();
	if (text.isEmpty())
	{
		return;
	}

	QString result_text = m_converter->convert(text);
	if (result_text.isEmpty())
	{
		QMessageBox::information(this, tr("tip"), m_converter->errorString());
	}
	else
	{
		ui.to_edit->setText(result_text);
	}
}

void ConverterDialog::onRevert()
{
	QString text = ui.to_edit->toPlainText();
	if (text.isEmpty())
	{
		return;
	}

	QString result_text = m_converter->revert(ui.to_edit->toPlainText());
	if (result_text.isEmpty())
	{
		QMessageBox::information(this, tr("tip"), m_converter->errorString());
	}
	else
	{
		ui.from_edit->setText(result_text);
	}
}