#include "tcp_response_dialog.h"

TcpResponseDialog::TcpResponseDialog(Tcp& tcp, QWidget *parent)
	: QDialog(parent, Qt::Dialog | Qt::WindowMaximizeButtonHint)
{
	m_rcv_thread = new RecvThread(tcp);

	ui.setupUi(this);
	setWindowTitle(tr("Response from server"));
	setWindowIcon(QIcon(":/npg/npg"));

	m_text_edit = new QTextEdit(this);
	ui.layout->addWidget(m_text_edit);

	connect(m_rcv_thread, SIGNAL(recvData(const QByteArray&)), this, SLOT(addData(const QByteArray&)));
	connect(m_rcv_thread, SIGNAL(finished(void)), this, SLOT(recvFinished(void)));
	connect(ui.close_button, SIGNAL(released(void)), this, SLOT(close(void)));
	
	m_rcv_thread->start();

	ui.tip_label->setText(tr("wait for response from server, please wait ..."));
}

TcpResponseDialog::~TcpResponseDialog()
{
	delete m_rcv_thread;
}


bool TcpResponseDialog::close()
{
	m_rcv_thread->stop();
	m_rcv_thread->wait();
	return QDialog::close();
}


void  TcpResponseDialog::addData(const QByteArray& data)
{
	if (data.length() <= 0)
	{
		return;
	}

	m_text_edit->append(data.data());
}

void TcpResponseDialog::recvFinished()
{
	if (!m_rcv_thread->error().isEmpty())
	{
		ui.tip_label->setText(QString("<font color=red>%1</font>").arg(m_rcv_thread->error()));
	}
	else
	{
		ui.tip_label->setText(QString("<font color=green>%1</font>").arg(tr("finished")));
	}
}

