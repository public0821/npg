#include "npg.h"

#include <qstringlist.h>
#include <qsettings.h>
#include "udp_widget.h"
#include "public.h"

npg::npg(QWidget *parent) :
		QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionQuit, SIGNAL(triggered(bool)), this, SLOT(onClose ()));
	ui.toolBar->addAction(ui.actionQuit);

	m_mainSplitter = new QSplitter(Qt::Horizontal);

	m_typeList = new MainListWidget();
	m_tabWidget = new MainTabWidget();

	m_mainSplitter->addWidget(m_typeList);
	m_mainSplitter->addWidget(m_tabWidget);
	m_mainSplitter->setStretchFactor(1, 1);

	setCentralWidget(m_mainSplitter);

	connect(m_typeList, SIGNAL(itemDoubleClicked(QListWidgetItem* )), this,
			SLOT(itemDoubleClicked(QListWidgetItem* )));

	restoreSettings();
//	m_tabWidget->addTab(new UdpWidget(m_tabWidget), "udp");
}

npg::~npg()
{

}

void npg::itemDoubleClicked(QListWidgetItem * item)
{
	if (item == NULL)
	{
		return;
	}

	QString data_type = item->text();
	m_tabWidget->addTab(data_type);

}

void npg::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);

	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("mainSplitter", m_mainSplitter->saveState());
	settings.endGroup();
}

void npg::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);

	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	m_mainSplitter->restoreState(settings.value("mainSplitter").toByteArray());
	settings.endGroup();
}

void npg::onClose()
{
	saveSettings();
	close();
}
