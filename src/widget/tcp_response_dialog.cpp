#include "tcp_response_dialog.h"

TcpResponseDialog::TcpResponseDialog(Tcp& tcp, QWidget *parent)
	: QDialog(parent, Qt::Dialog | Qt::WindowMaximizeButtonHint)
//	,m_tcp(tcp)
{
	m_rcv_thread = new RecvThread(tcp);

	ui.setupUi(this);
	setWindowTitle(tr("Response from server"));
	setWindowIcon(QIcon(":/npg/npg"));

	m_text_edit = new QTextEdit(this);
	m_html = new QWebView(this);
	ui.layout->addWidget(m_text_edit);
	ui.layout->addWidget(m_html);
	m_html->setVisible(false);
	ui.html_checkbox->setEnabled(false);

	connect(m_rcv_thread, SIGNAL(recvData(const QString&)), this, SLOT(addData(const QString&)));
	connect(m_rcv_thread, SIGNAL(finished(void)), this, SLOT(recvFinished(void)));
	connect(ui.close_button, SIGNAL(released(void)), this, SLOT(close(void)));
	connect(ui.html_checkbox, SIGNAL(stateChanged(int)), this, SLOT(showText(int)));

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


void  TcpResponseDialog::addData(const QString& data)
{
	m_text_edit->append(data);
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

	ui.html_checkbox->setEnabled(true);
}

void TcpResponseDialog::showText(int state)
{
	if (state == Qt::Checked)
	{
		m_text_edit->setVisible(false);
		m_html->setVisible(true);
		m_html->setHtml(m_text_edit->toPlainText());
	}
	else
	{
		m_html->setVisible(false);
		m_text_edit->setVisible(true);
	}
}