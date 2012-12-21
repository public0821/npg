#include "tcp_response_dialog.h"
#include "qresource.h"

TcpResponseDialog::TcpResponseDialog(Tcp& tcp, QWidget *parent)
:
		QDialog(parent, Qt::Dialog | Qt::WindowMaximizeButtonHint)
{
	m_rcv_thread = new RecvThread(tcp);

	ui.setupUi(this);
	setWindowTitle(tr("Response from server"));
	setWindowIcon(QIcon(ICON_NPG));

	m_text_edit = new QTextEdit(this);
	ui.layout->addWidget(m_text_edit);

	connect(m_rcv_thread, SIGNAL(recvData(const QByteArray&)), this, SLOT(onAddData(const QByteArray&)));
	connect(m_rcv_thread, SIGNAL(finished(void)), this, SLOT(onRecvFinished(void)));
	connect(ui.close_button, SIGNAL(released(void)), this, SLOT(onClose(void)));

	m_rcv_thread->start();

	ui.tip_label->setText(tr("wait for response from server, please wait ..."));
}

TcpResponseDialog::~TcpResponseDialog()
{
	delete m_rcv_thread;
}

bool TcpResponseDialog::onClose()
{
	m_rcv_thread->stop();
	m_rcv_thread->wait();
	return QDialog::close();
}

void TcpResponseDialog::onAddData(const QByteArray& data)
		{
	if (data.length() <= 0)
			{
		return;
	}

	m_text_edit->append(data.data());
}

void TcpResponseDialog::onRecvFinished() {
	if (m_rcv_thread->error_happend()) {
		ui.tip_label->setText(QString("<font color=red>%1</font>").arg(tr("error happened")));
	} else {
		ui.tip_label->setText(QString("<font color=green>%1</font>").arg(tr("finished")));
	}
}

