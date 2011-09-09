#ifndef NPG_H
#define NPG_H

#include <QtGui/QMainWindow>
#include "ui_npg.h"
#include <QListWidget>
#include <QTabWidget>
#include <QSplitter>
#include "main_list_widget.h"
#include "main_tab_widget.h"

class npg: public QMainWindow
{
Q_OBJECT

public:
	npg(QWidget *parent = 0);
	~npg();
private slots:
	void itemDoubleClicked(QListWidgetItem * item);
	void onClose();
private:
	void saveSettings();
	void restoreSettings();
private:
	Ui::npgClass ui;
	MainListWidget* m_typeList;
	MainTabWidget* m_tabWidget;
	QSplitter* m_mainSplitter;
//	QStringList m_data_types;
};

#endif // NPG_H
