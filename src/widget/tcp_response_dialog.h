/*
 * tcp_response_dialog.h
 *
 *  Created on: 2011-12-10
 *      Author: Young <public0821@gmail.com>
 */
#ifndef TCP_REPONSE_DIALOG_H
#define TCP_REPONSE_DIALOG_H

#include <QDialog>
#include "ui_tcp_response_dialog.h"
#include "socket/tcp.h"
#include <qtextedit.h>
#include "socket/socket_public.h"

class RecvThread;
class TcpResponseDialog : public QDialog
{
	Q_OBJECT

public:
	TcpResponseDialog(Tcp& tcp, QWidget *parent = 0);
	~TcpResponseDialog();
private slots:
	void  onAddData(const QByteArray& data);
	bool onClose();
	void onRecvFinished();
private:
	Ui::TcpReponseDialog ui;
	RecvThread* m_rcv_thread;
	QTextEdit* m_text_edit;
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
signals:
	void recvData(const QByteArray&);
private:
	void run()
	{
		const size_t buff_len = 1023;
		char buff[buff_len+1];

		bool ret = m_tcp.setBlocking(false);
		if (!ret)
		{
			m_error = m_tcp.errorString();
			return;
		}

		while(m_running)
		{
			int len = m_tcp.recv(buff, buff_len);
			if (len == -1)
			{
				m_error = m_tcp.errorString();
				break;
			}
			
			buff[len] = '\0';
			emit recvData(QByteArray(buff));

			if ((size_t)len < buff_len && m_tcp.status() == E_ERROR_STATUS_SOCKET_CLOSED )//the peer has performed an orderly shutdown
			{
				break;
			}
			
			if (len == 0)
			{
				sleep(1);
			}
		}	

		ret = m_tcp.setBlocking(true);
		if (!ret)
		{
			m_error = m_tcp.errorString();
			return;
		}
	};
private:
	volatile bool m_running;
	QString m_error;

	Tcp& m_tcp;
};
#endif // TCP_REPONSE_DIALOG_H
