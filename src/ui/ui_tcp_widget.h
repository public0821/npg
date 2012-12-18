/********************************************************************************
** Form generated from reading UI file 'tcp_widget.ui'
**
** Created: Tue Dec 18 16:31:01 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCP_WIDGET_H
#define UI_TCP_WIDGET_H

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
#include <QtGui/QWidget>
#include "widget/ip_combobox.h"

QT_BEGIN_NAMESPACE

class Ui_TcpWidgetClass
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *dip_edit;
    QLabel *label;
    QLineEdit *dport_edit;
    QLabel *label_5;
    QLabel *label_4;
    QLineEdit *sport_edit;
    IpComboBox *sip_box;
    QLabel *label_3;
    QCheckBox *wait_for_response_box;
    QCheckBox *src_ip_box;
    QSpacerItem *horizontalSpacer;
    QLineEdit *timeout_edit;

    void setupUi(QWidget *TcpWidgetClass)
    {
        if (TcpWidgetClass->objectName().isEmpty())
            TcpWidgetClass->setObjectName(QString::fromUtf8("TcpWidgetClass"));
        TcpWidgetClass->resize(557, 219);
        gridLayout = new QGridLayout(TcpWidgetClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(TcpWidgetClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 1, -1, -1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 4, 0, 1, 1);

        dip_edit = new QLineEdit(groupBox);
        dip_edit->setObjectName(QString::fromUtf8("dip_edit"));

        gridLayout_2->addWidget(dip_edit, 4, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 4, 2, 1, 1);

        dport_edit = new QLineEdit(groupBox);
        dport_edit->setObjectName(QString::fromUtf8("dport_edit"));

        gridLayout_2->addWidget(dport_edit, 4, 3, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 1, 2, 1, 1);

        sport_edit = new QLineEdit(groupBox);
        sport_edit->setObjectName(QString::fromUtf8("sport_edit"));

        gridLayout_2->addWidget(sport_edit, 1, 3, 1, 1);

        sip_box = new IpComboBox(groupBox);
        sip_box->setObjectName(QString::fromUtf8("sip_box"));

        gridLayout_2->addWidget(sip_box, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 4, 4, 1, 1);

        wait_for_response_box = new QCheckBox(groupBox);
        wait_for_response_box->setObjectName(QString::fromUtf8("wait_for_response_box"));

        gridLayout_2->addWidget(wait_for_response_box, 4, 6, 1, 1);

        src_ip_box = new QCheckBox(groupBox);
        src_ip_box->setObjectName(QString::fromUtf8("src_ip_box"));

        gridLayout_2->addWidget(src_ip_box, 1, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 5, 1, 1);

        timeout_edit = new QLineEdit(groupBox);
        timeout_edit->setObjectName(QString::fromUtf8("timeout_edit"));

        gridLayout_2->addWidget(timeout_edit, 4, 5, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(TcpWidgetClass);

        QMetaObject::connectSlotsByName(TcpWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *TcpWidgetClass)
    {
        TcpWidgetClass->setWindowTitle(QApplication::translate("TcpWidgetClass", "TcpWidget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TcpWidgetClass", "TCP", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TcpWidgetClass", "dst ip", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TcpWidgetClass", "dst port", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("TcpWidgetClass", "src ip", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TcpWidgetClass", "src port", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TcpWidgetClass", "timeout", 0, QApplication::UnicodeUTF8));
        wait_for_response_box->setText(QApplication::translate("TcpWidgetClass", "wait for response", 0, QApplication::UnicodeUTF8));
        src_ip_box->setText(QApplication::translate("TcpWidgetClass", "system asign", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TcpWidgetClass: public Ui_TcpWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_WIDGET_H
