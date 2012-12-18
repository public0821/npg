/********************************************************************************
** Form generated from reading UI file 'udp_widget.ui'
**
** Created: Tue Dec 18 16:40:37 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDP_WIDGET_H
#define UI_UDP_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "widget/ip_combobox.h"

QT_BEGIN_NAMESPACE

class Ui_UdpWidgetClass
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *src_ip_label;
    QLabel *label_3;
    QLineEdit *src_port_edit;
    QCheckBox *src_ip_checkbox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *dst_ip_edit;
    QLabel *label_2;
    QLineEdit *dst_port_edit;
    QSpacerItem *horizontalSpacer_2;
    IpComboBox *src_ip_combobox;

    void setupUi(QWidget *UdpWidgetClass)
    {
        if (UdpWidgetClass->objectName().isEmpty())
            UdpWidgetClass->setObjectName(QString::fromUtf8("UdpWidgetClass"));
        UdpWidgetClass->resize(308, 90);
        verticalLayout = new QVBoxLayout(UdpWidgetClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(UdpWidgetClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 1, 9, 9);
        src_ip_label = new QLabel(groupBox);
        src_ip_label->setObjectName(QString::fromUtf8("src_ip_label"));
        src_ip_label->setLayoutDirection(Qt::RightToLeft);
        src_ip_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(src_ip_label, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        src_port_edit = new QLineEdit(groupBox);
        src_port_edit->setObjectName(QString::fromUtf8("src_port_edit"));

        gridLayout->addWidget(src_port_edit, 0, 3, 1, 1);

        src_ip_checkbox = new QCheckBox(groupBox);
        src_ip_checkbox->setObjectName(QString::fromUtf8("src_ip_checkbox"));

        gridLayout->addWidget(src_ip_checkbox, 0, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        dst_ip_edit = new QLineEdit(groupBox);
        dst_ip_edit->setObjectName(QString::fromUtf8("dst_ip_edit"));

        gridLayout->addWidget(dst_ip_edit, 1, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 2, 1, 1);

        dst_port_edit = new QLineEdit(groupBox);
        dst_port_edit->setObjectName(QString::fromUtf8("dst_port_edit"));

        gridLayout->addWidget(dst_port_edit, 1, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 2);

        src_ip_combobox = new IpComboBox(groupBox);
        src_ip_combobox->setObjectName(QString::fromUtf8("src_ip_combobox"));

        gridLayout->addWidget(src_ip_combobox, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox);


        retranslateUi(UdpWidgetClass);

        QMetaObject::connectSlotsByName(UdpWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *UdpWidgetClass)
    {
        UdpWidgetClass->setWindowTitle(QApplication::translate("UdpWidgetClass", "UdpWidget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("UdpWidgetClass", "UDP", 0, QApplication::UnicodeUTF8));
        src_ip_label->setText(QApplication::translate("UdpWidgetClass", "SRC_IP", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("UdpWidgetClass", "SRC_PORT ", 0, QApplication::UnicodeUTF8));
        src_ip_checkbox->setText(QApplication::translate("UdpWidgetClass", "default", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UdpWidgetClass", "DST_IP", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("UdpWidgetClass", "DST_PORT ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UdpWidgetClass: public Ui_UdpWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDP_WIDGET_H
