#ifndef NPG_H
#define NPG_H

#include <QtGui/QMainWindow>
#include "ui_npg.h"
#include <QListWidget>
#include <QTabWidget>

const QString K_UDP = "UDP";
const QString K_TCP = "TCP";

class npg : public QMainWindow
{
    Q_OBJECT

public:
    npg(QWidget *parent = 0);
    ~npg();
private slots:
	void itemDoubleClicked(QListWidgetItem * item);
private:
    Ui::npgClass ui;
	QListWidget*	m_typeList;
	QTabWidget*		m_tabWidget;
//	QStringList m_data_types;
private:
	QIcon	m_icon_udp;
};

#endif // NPG_H
