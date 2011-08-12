#include "npg.h"
#include <QHBoxLayout>
#include <qstringlist.h>

#include "udp_widget.h"

npg::npg(QWidget *parent) :
		QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionQuit, SIGNAL(triggered(bool)), this, SLOT(close ()));
	ui.toolBar->addAction(ui.actionQuit);

	QHBoxLayout *mainLayout = new QHBoxLayout(ui.centralwidget);

	m_typeList = new QListWidget(ui.centralwidget);
	m_tabWidget = new QTabWidget(ui.centralwidget);

	mainLayout->addWidget(m_typeList);
	mainLayout->addWidget(m_tabWidget);
	mainLayout->setStretch(1, 1);

	m_icon_udp.addFile(QString::fromUtf8(":/npg/resource/udp.png"), QSize(), QIcon::Normal, QIcon::Off);

	m_typeList->setViewMode(QListView::IconMode);
	m_typeList->setFlow(QListView::TopToBottom);
	QListWidgetItem* udp = new QListWidgetItem(m_icon_udp, K_UDP, m_typeList);
	QListWidgetItem* tcp = new QListWidgetItem(m_icon_udp, K_TCP, m_typeList);
	udp->setTextAlignment(Qt::AlignHCenter);
	tcp->setTextAlignment(Qt::AlignHCenter);
	connect(m_typeList, SIGNAL(itemDoubleClicked(QListWidgetItem* )), this,
			SLOT(itemDoubleClicked(QListWidgetItem* )));


	m_tabWidget->setTabsClosable(true);
	m_tabWidget->setMovable(true);

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
	if (data_type == K_UDP)
	{
		m_tabWidget->addTab(new UdpWidget(m_tabWidget), m_icon_udp, K_UDP);
	}
}
