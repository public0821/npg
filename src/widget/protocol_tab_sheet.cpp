/*
 * dns_widget.cpp
 *
 *  Created on: 2011-10-11
 *      Author: Young <public0821@gmail.com>
 */

#include "protocol_tab_sheet.h"
#include <qsettings.h>
#include "npg_define.h"
#include "protocol_tree_item_widget.h"
#include "protocol/protocol_builder.h"
#include "base_protocol/udp_widget.h"
#include "../logger.h"
#include "lib/socket/toolkit.h"
#include "protocol/bit_builder.h"

ProtocolTabSheet::ProtocolTabSheet(const Protocol& protocol, QWidget *parent)
:
		TabSheet(protocol.name(), parent, protocol.dependenceString(), protocol.dependenceParam())
				, m_protocol(protocol)
				, m_seq(0)
{
	ui.setupUi(this);
	ui.treeWidget->setup(protocol);
	setupUi(ui.advanced_layout);
	ui.protocol_layout->addWidget(dependProtocolWidget());
	//ui.group_box->setTitle(protocol.dependenceString().c_str());
	connect(ui.load_config_button, SIGNAL(released()), ui.treeWidget, SLOT(onRestoreSettings()));
	connect(ui.save_config_button, SIGNAL(released()), ui.treeWidget, SLOT(onSaveSettings()));
}

ProtocolTabSheet::~ProtocolTabSheet()
{

}

void ProtocolTabSheet::saveSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_protocol.name());
	//settings.setValue("server", ui.server_edit->text());
	//settings.setValue("request", ui.request_edit->text());
	//settings.setValue("reverse", (int)ui.reverse_checkbox->checkState());
	settings.endGroup();
	TabSheet::saveSettings();
}

void ProtocolTabSheet::restoreSettings()
{
	QSettings settings(K_SETTING_COMPANY, K_SETTING_APP);
	settings.beginGroup(m_protocol.name());
	//ui.server_edit->setText(settings.value("server").toString());
	//ui.request_edit->setText(settings.value("request").toString());
	//ui.reverse_checkbox->setCheckState((Qt::CheckState)settings.value("reverse").toInt());
	settings.endGroup();
	TabSheet::restoreSettings();
}

bool ProtocolTabSheet::preSendData()
{
	ProtocolBuilder protocol_builder;

	ProtocolTree* tree_widget = ui.treeWidget;
	int category_count = tree_widget->topLevelItemCount();
	for (int category_index = 0; category_index < category_count; category_index++) {
		QTreeWidgetItem* category_item = tree_widget->topLevelItem(category_index);
		QString category_name = category_item->data(1, Qt::UserRole).toString();
		Category category = m_protocol.category(category_name);
		QString category_prefix = category.prefix();
		if (!category_prefix.isEmpty()) {
			QByteArray category_prefix_array = category_prefix.toLocal8Bit();
			int ret = protocol_builder.append(category_prefix_array.constData(), category_prefix_array.size());
			if (ret == false) {
				return false;
			}
		}

		int field_count = category_item->childCount();
		for (int field_index = 0; field_index < field_count; field_index++) {
			QTreeWidgetItem* field_item = category_item->child(field_index);
			QString field_name = field_item->data(1, Qt::UserRole).toString();
			Field field = category.field(field_name);

			QString field_prefix = field.prefix();
			if (!field_prefix.isEmpty()) {
				QByteArray field_prefix_array = field_prefix.toLocal8Bit();
				int ret = protocol_builder.append(field_prefix_array.constData(), field_prefix_array.size());
				if (ret == false) {
					return false;
				}
			}

			int sub_field_count = field_item->childCount();
			if (sub_field_count > 0) {
				if (field.length() <= 0) {
					LOG_ERROR(tr("field length must greater than 0:") + field.name());
					return false;
				}

				BitBuilder bit_builder(field.length());
				for (int sub_field_index = 0; sub_field_index < sub_field_count; sub_field_index++) {
					QTreeWidgetItem* sub_field_item = field_item->child(sub_field_index);
					ProtocolTreeItemWidget* item_widget = (ProtocolTreeItemWidget*) tree_widget->itemWidget(sub_field_item, 1);
					uint32_t data = item_widget->value().toUInt();

					QString sub_field_name = sub_field_item->data(1, Qt::UserRole).toString();
					Field sub_field = field.subField(sub_field_name);
					int ret = bit_builder.append(data, sub_field.length());
					if (ret == false) {
						return false;
					}
				}
				int ret = protocol_builder.append((const char *) bit_builder.data(), bit_builder.length());
				if (ret == false) {
					return false;
				}

			} else { //sub_field_count == 0

				QCheckBox* item_checkbox = (QCheckBox*) tree_widget->itemWidget(field_item, 2);
				QString data;
				if (item_checkbox != NULL && item_checkbox->checkState() == Qt::Unchecked) {
					data = FieldDefaultValue::instance().calcValue(field.defaultValue());
				} else {
					ProtocolTreeItemWidget* item_widget = (ProtocolTreeItemWidget*) tree_widget->itemWidget(field_item, 1);
					data = item_widget->value();
				}

				bool ret = protocol_builder.append(field.type(), field.length(), data);
				if (ret == false) {
					return false;
				}
			}

			QString field_suffix = field.suffix();
			if (!field_suffix.isEmpty()) {
				QByteArray field_suffix_array = field_suffix.toLocal8Bit();
				int ret = protocol_builder.append(field_suffix_array.constData(), field_suffix_array.size());
				if (ret == false) {
					return false;
				}
			}

		}

		QString category_suffix = category.suffix();
		if (!category_suffix.isEmpty()) {
			QByteArray category_suffix_array = category_suffix.toLocal8Bit();
			int ret = protocol_builder.append(category_suffix_array.constData(), category_suffix_array.size());
			if (ret == false) {
				return false;
			}
		}

	}

	m_data.assign(protocol_builder.data(), protocol_builder.length());

	return dependProtocolWidget()->preSendData();
}

bool ProtocolTabSheet::postSendData()
{
	m_data.clear();
	return dependProtocolWidget()->postSendData();
}

//#include <qmessagebox.h>
bool ProtocolTabSheet::sendData()
{
	return dependProtocolWidget()->sendData(m_data.data(), m_data.length());
}
