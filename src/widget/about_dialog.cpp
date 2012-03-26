#include "about_dialog.h"

AboutDialog::AboutDialog(QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
	ui.setupUi(this);
	setWindowTitle(tr("About NPG"));
	ui.label->setWordWrap(true);
	ui.label->setMinimumSize (300, 200);
	ui.label->setText(tr("  Netword packet generator(NPG) is a tool used to construct and send packets, the purpose is to help the developers of network easily constructed test data.\
						 \n  NPG's feature is by modifying the configuration file can support a variety of packet formats\
						 \n  Author:public0821@gmail.com"));
//	ui.label->adjustSize();
}

AboutDialog::~AboutDialog()
{

}
