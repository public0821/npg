#include "converter_dialog.h"
#include <QMessageBox>
#include "tools/ip_converter.h"
#include "tools/hex_converter.h"
#include "tools/time_converter.h"
#include "tools/base64_converter.h"

ConverterDialog::ConverterDialog(EConverterType type, const QIcon& icon, QWidget *parent)
	:QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
	ui.setupUi(this);

	m_converter = NULL;
	switch (type)
	{
	case E_CONVERTER_IP:
		m_converter = new IpConverter();
		break;
	case E_CONVERTER_HEX:
		m_converter = new HexConverter();
		break;
	case E_CONVERTER_TIME:
		m_converter = new TimeConverter();
		break;
	case E_CONVERTER_BASE64:
		m_converter = new Base64Converter();
		break;
	default:
		return;
	}

	setWindowTitle(m_converter->title());
	setWindowIcon(icon);

	ui.from_label->setText(m_converter->fromTextTip());
	ui.to_label->setText(m_converter->toTextTip());

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
