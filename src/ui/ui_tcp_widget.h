/********************************************************************************
** Form generated from reading UI file 'tcp_widget.ui'
**
** Created: Mon Dec 17 11:38:33 2012
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

QT_BEGIN_NAMESPACE

class Ui_TcpWidgetClass
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLineEdit *ip_edit;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLineEdit *timeout_edit;
    QSpacerItem *horizontalSpacer;
    QLineEdit *port_edit;
    QCheckBox *wait_for_response_box;

    void setupUi(QWidget *TcpWidgetClass)
    {
        if (TcpWidgetClass->objectName().isEmpty())
            TcpWidgetClass->setObjectName(QString::fromUtf8("TcpWidgetClass"));
        TcpWidgetClass->resize(273, 96);
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

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        ip_edit = new QLineEdit(groupBox);
        ip_edit->setObjectName(QString::fromUtf8("ip_edit"));

        gridLayout_2->addWidget(ip_edit, 0, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        timeout_edit = new QLineEdit(groupBox);
        timeout_edit->setObjectName(QString::fromUtf8("timeout_edit"));

        gridLayout_2->addWidget(timeout_edit, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 4, 1, 2);

        port_edit = new QLineEdit(groupBox);
        port_edit->setObjectName(QString::fromUtf8("port_edit"));

        gridLayout_2->addWidget(port_edit, 0, 3, 1, 1);

        wait_for_response_box = new QCheckBox(groupBox);
        wait_for_response_box->setObjectName(QString::fromUtf8("wait_for_response_box"));

        gridLayout_2->addWidget(wait_for_response_box, 1, 3, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 5);


        retranslateUi(TcpWidgetClass);

        QMetaObject::connectSlotsByName(TcpWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *TcpWidgetClass)
    {
        TcpWidgetClass->setWindowTitle(QApplication::translate("TcpWidgetClass", "TcpWidget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TcpWidgetClass", "TCP", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TcpWidgetClass", "IP:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TcpWidgetClass", "Port:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TcpWidgetClass", "Timeout:", 0, QApplication::UnicodeUTF8));
        wait_for_response_box->setText(QApplication::translate("TcpWidgetClass", "WaitForResponse", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TcpWidgetClass: public Ui_TcpWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_WIDGET_H
