#ifndef TCP_REPONSE_DIALOG_H
#define TCP_REPONSE_DIALOG_H

#include <QDialog>
#include "ui_tcp_response_dialog.h"
#include "socket/tcp.h"
#include <qtextedit.h>
#include <QWebView>
#include "socket/socket_public.h"

class RecvThread;
class TcpResponseDialog : public QDialog
{
	Q_OBJECT

public:
	TcpResponseDialog(Tcp& tcp, QWidget *parent = 0);
	~TcpResponseDialog();
private slots:
	void  addData(const QString& data);
	bool close();
	void recvFinished();
	void showText(int state);
private:
	Ui::TcpReponseDialog ui;
//	Tcp& m_tcp;
	RecvThread* m_rcv_thread;
	QTextEdit* m_text_edit;
	QWebView* m_html;
};


#include <qthread.h>
class RecvThread: public QThread
{
	Q_OBJECT
public:
	RecvThread(Tcp& tcp):m_tcp(tcp){};
	~RecvThread(){};
public:
	void stop()
	{
		m_running = false;
	}

	const QString& error() const
	{
		return m_error;
	}
	;
	//	bool isRunning() const
	//	{
	//		return m_running;
	//	}
signals:
	//	void error(const QString&);
	void recvData(const QString& data);
private:
	void run()
	{
		const size_t buff_len = 1023;
		char buff[buff_len+1];

		bool ret = m_tcp.setBlocking(false);
		if (!ret)
		{
			m_error = m_tcp.error();
			return;
		}

		while(m_running)
		{
			size_t len = m_tcp.recv(buff, buff_len);
			if (len == -1)
			{
				m_error = m_tcp.error();
				break;
			}
			
			buff[len] = '\0';
			emit recvData(buff);

			int error_no = npg_errno;
			if (len < buff_len && error_no != EWOULDBLOCK && error_no != EAGAIN )//the peer has performed an orderly shutdown
			{
				break;
			}
		}	

		ret = m_tcp.setBlocking(true);
		if (!ret)
		{
			m_error = m_tcp.error();
			return;
		}
	};
private:
	volatile bool m_running;
	QString m_error;

	Tcp& m_tcp;
};
#endif // TCP_REPONSE_DIALOG_H
