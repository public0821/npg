#include "base_protocol_widget.h"

BaseProtocolWidget::BaseProtocolWidget(const QString& full_protocol_name, QWidget *parent)
	: QWidget(parent), m_full_protocol_name(full_protocol_name)
{

}

BaseProtocolWidget::~BaseProtocolWidget()
{

}

//void BaseProtocolWidget::setupUi(QHBoxLayout* layout, QWidget* show_widget)
//{
//	layout->setContentsMargins(0,0,0,0);
//	layout->setSpacing(0);
//	m_show_button = new QPushButton(this);
//	layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
//	layout->addWidget(m_show_button);
//	layout->addItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));	
//	connect(m_show_button, SIGNAL(released(void)), this, SLOT(onShowButton(void)));
//	m_show = true;
//	m_show_widget = show_widget;
//	m_show_button->setIcon(QIcon(ICON_UP));
//}
//
//void BaseProtocolWidget::onShowButton()
//{
//	if (m_show)
//	{
//		m_show_widget->setVisible(false);
//		m_show = false;
//		m_show_button->setIcon(QIcon(ICON_DOWN));
//	}
//	else
//	{
//		m_show_widget->setVisible(true);
//		m_show = true;
//		m_show_button->setIcon(QIcon(ICON_UP));
//	}
//}
