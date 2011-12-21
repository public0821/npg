/*
 * dns_widget.cpp
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */


#include "protocol_tab_sheet.h"
#include <qsettings.h>
#include "npg_define.h"
#include "protocol_tree_item.h"
#include "protocol/protocol_builder.h"
#include "udp_widget.h"

ProtocolTabSheet::ProtocolTabSheet(const Protocol& protocol, QWidget *parent) 
:TabSheet(protocol.name().c_str(), parent, protocol.dependenceString().c_str(), protocol.DependenceParam().c_str())
, m_protocol(protocol)
{
	ui.setupUi(this);
	ui.treeWidget->setup(protocol);
	setupUi(ui.advanced_layout);
	ui.protocol_layout->addWidget(dependProtocolWidget());
	//ui.group_box->setTitle(protocol.dependenceString().c_str());
}

ProtocolTabSheet::~ProtocolTabSheet()
{

}

void ProtocolTabSheet::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_protocol.name().c_str());
	//settings.setValue("server", ui.server_edit->text());
	//settings.setValue("request", ui.request_edit->text());
	//settings.setValue("reverse", (int)ui.reverse_checkbox->checkState());
	settings.endGroup();
	TabSheet::saveSettings();
}

void ProtocolTabSheet::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_protocol.name().c_str());
	//ui.server_edit->setText(settings.value("server").toString());
	//ui.request_edit->setText(settings.value("request").toString());
	//ui.reverse_checkbox->setCheckState((Qt::CheckState)settings.value("reverse").toInt());
	settings.endGroup();
	TabSheet::restoreSettings();
}

//#include <qmessagebox.h>
QString ProtocolTabSheet::sendData()
{
	ProtocolBuilder protocol_builder;
	ProtocolTree* tree_widget = ui.treeWidget;
	int	category_count = tree_widget->topLevelItemCount();
	for (int i = 0; i < category_count; i++)
	{
		QTreeWidgetItem* category_item = tree_widget->topLevelItem(i);
		QString category_name = category_item->data(1, Qt::UserRole).toString();
		Category category = m_protocol.category(category_name.toStdString());

		int field_count = category_item->childCount();
		for (int j = 0; j < field_count; j++)
		{
			QTreeWidgetItem* field_item	= category_item->child (j);
			ProtocolTreeItem* item = (ProtocolTreeItem*)tree_widget->itemWidget(field_item, 1);
			QString field_name = field_item->data(1, Qt::UserRole).toString();
			Field field = category.field(field_name.toStdString());
			bool ret = protocol_builder.append(field.type(), field.length(), item->value());
			if (ret == false)
			{
				return protocol_builder.errorStr();
			}
			
		}
	}


	BaseProtocolWidget* depend_protocol_widget = dependProtocolWidget();
	if (depend_protocol_widget != NULL)
	{
		return depend_protocol_widget->sendData(protocol_builder.data(), protocol_builder.length());
	}
	else
	{
		return tr("incorrect dependence protocol");
	}
	
	//QMessageBox::information(this, "tip", QString("%1").arg(protocol_builder.length()));
}
