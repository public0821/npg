/*
 * main_tab_widget.cpp
 *
 *  Created on: 2011-8-19
 *      Author: Young <public0821@gmail.com>
 */

#include "main_tab_widget.h"
#include "config.h"
#include "data_tab_sheet.h"
#include "base_protocol/tcp_widget.h"
#include "protocol/protocol_factory.h"
#include "protocol_tab_sheet.h"

MainTabWidget::MainTabWidget(const QMap<QString, QString>& internal_protocol, QWidget* parent)
:
		QTabWidget(parent), m_internal_protocol(internal_protocol) {
	setTabsClosable(true);
	setMovable(true);

	connect(this, SIGNAL(tabCloseRequested (int)), this,
			SLOT(onCloseTab (int)));
}

MainTabWidget::~MainTabWidget() {
}

void MainTabWidget::onCloseTab(int index) {
	removeTab(index);
	delete m_tabs[index];
	m_tabs.remove(index);
}

int MainTabWidget::addTab(const QString &type) {
	int index = -1;
	TabSheet* sheet = NULL;

	QMap<QString, QString>::const_iterator it = m_internal_protocol.find(type);
	if (it != m_internal_protocol.end()) {
		sheet = new DataTabSheet(type, this);
		index = QTabWidget::addTab(sheet, QIcon(it.value()), it.key());
	} else {
		Protocol protocol = ProtocolFactory::instance().protocol(type);
		if (!protocol.empty()) {
			sheet = new ProtocolTabSheet(protocol, this);
			index = QTabWidget::addTab(sheet, QIcon(protocol.icon()), type);
		}

	}

	if (index != -1) {
		m_tabs.push_back(sheet);
		setCurrentIndex(index);
	}

	return index;
}
