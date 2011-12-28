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
#include "socket/socket_toolkit.h"
#include "protocol/bit_builder.h"

ProtocolTabSheet::ProtocolTabSheet(const Protocol& protocol, QWidget *parent) 
:TabSheet(protocol.name().c_str(), parent, protocol.dependenceString().c_str(), protocol.DependenceParam().c_str())
, m_protocol(protocol)
,m_seq(0)
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

	bool need_checknum = false;
	u_int16_t checknum_pos = 0;
	Field checknum_field("", true);

	ProtocolTree* tree_widget = ui.treeWidget;
	int	category_count = tree_widget->topLevelItemCount();
	for (int category_index = 0; category_index < category_count; category_index++)
	{
		QTreeWidgetItem* category_item = tree_widget->topLevelItem(category_index);
		QString category_name = category_item->data(1, Qt::UserRole).toString();
		Category category = m_protocol.category(category_name.toStdString());

		int field_count = category_item->childCount();
		for (int field_index = 0; field_index < field_count; field_index++)
		{
			QTreeWidgetItem* field_item	= category_item->child (field_index);
			QString field_name = field_item->data(1, Qt::UserRole).toString();
			Field field = category.field(field_name.toStdString());

			int sub_field_count = field_item->childCount();
			if (sub_field_count > 0)
			{
				if (field.length() <= 0)
				{
					return tr("field length must greater than 1:") + field.name().c_str();
				}
				
				BitBuilder bit_builder(field.length());
				for (int sub_field_index = 0; sub_field_index < sub_field_count; sub_field_index++)
				{
					QTreeWidgetItem* sub_field_item	= field_item->child (sub_field_index);
					ProtocolTreeItem* item_widget = (ProtocolTreeItem*)tree_widget->itemWidget(sub_field_item, 1);
					u_int32_t data = item_widget->value().toUInt();

					QString sub_field_name = sub_field_item->data(1, Qt::UserRole).toString();
					Field sub_field = field.subField(sub_field_name.toStdString());
					bit_builder.append(data, sub_field.length());
				}
				protocol_builder.append((const char *)bit_builder.data(), bit_builder.length());
			}
			else
			{
				QCheckBox* item_checkbox = (QCheckBox*)tree_widget->itemWidget(field_item, 2);
				QString data;
				if (item_checkbox != NULL && item_checkbox->checkState() == Qt::Unchecked)
				{
					if (field.defaultValueOriginal() == K_DEFAULT_VALUE_CHECKNUM)
					{
						need_checknum = true;
						checknum_pos = protocol_builder.length();
						checknum_field = field;
					}	
					data = convertDefaultValue(field.defaultValueOriginal().c_str());
				}
				else
				{
					ProtocolTreeItem* item_widget = (ProtocolTreeItem*)tree_widget->itemWidget(field_item, 1);
					data = item_widget->value();
				}

				bool ret = protocol_builder.append(field.type(), field.length(), data);
				if (ret == false)
				{
					return protocol_builder.errorStr();
				}
			}
			
			
		}
	}

	if (need_checknum)
	{
		SocketToolkit toolkit;
		u_int16_t checknum = toolkit.inCheckSum((u_int16_t *)protocol_builder.data(), protocol_builder.length());
		checknum = ntohs(checknum);
		QString data = QString("%1").arg(checknum);
		protocol_builder.set(checknum_pos, checknum_field.type(), checknum_field.length(), data);
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


QString ProtocolTabSheet::convertDefaultValue(const QString& default_value)
{
	if (default_value == K_DEFAULT_VALUE_SECOND)
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		return QString("%1").arg(now.tv_sec);
	}
	else if (default_value == K_DEFAULT_VALUE_PID)
	{
		return QString("%1").arg(getpid());
	}
	else if (default_value == K_DEFAULT_VALUE_MILLISECOND)
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		return QString("%1").arg(now.tv_usec);
	}
	else if (default_value == K_DEFAULT_VALUE_CHECKNUM)
	{
		return QString("%1").arg(0);
	}
	else if (default_value == K_DEFAULT_VALUE_SEQ)
	{
		return QString("%1").arg(++m_seq);
	}
	else
	{
		return QString("%1").arg(0);
	}
	
}