#ifndef TCP_REPONSE_DIALOG_H
#define TCP_REPONSE_DIALOG_H

#include <QDialog>
#include "ui_tcp_response_dialog.h"
#include "socket/tcp.h"

class TcpResponseDialog : public QDialog
{
	Q_OBJECT

public:
	TcpResponseDialog(Tcp& tcp, QWidget *parent = 0);
	~TcpResponseDialog();

private:
	Ui::TcpReponseDialog ui;
	Tcp& m_tcp;
};

#endif // TCP_REPONSE_DIALOG_H
