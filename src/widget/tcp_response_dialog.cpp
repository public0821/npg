#include "tcp_response_dialog.h"

TcpResponseDialog::TcpResponseDialog(Tcp& tcp, QWidget *parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
	,m_tcp(tcp)
{
	ui.setupUi(this);
	setWindowTitle(tr("Response from server"));
	setWindowIcon(QIcon(":/npg/npg"));
}

TcpResponseDialog::~TcpResponseDialog()
{

}
