/********************************************************************************
** Form generated from reading UI file 'ethernet_widget.ui'
**
** Created: Tue Dec 18 11:10:10 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ETHERNET_WIDGET_H
#define UI_ETHERNET_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EthernetWidget
{
public:
    QGridLayout *gridLayout_2;
    QGroupBox *GroupBox;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QComboBox *interface_box;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLineEdit *to_mac_edit;
    QLabel *label_7;
    QLineEdit *from_mac_edit;
    QLabel *label_9;
    QComboBox *protocol_box;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *EthernetWidget)
    {
        if (EthernetWidget->objectName().isEmpty())
            EthernetWidget->setObjectName(QString::fromUtf8("EthernetWidget"));
        EthernetWidget->resize(407, 96);
        gridLayout_2 = new QGridLayout(EthernetWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        GroupBox = new QGroupBox(EthernetWidget);
        GroupBox->setObjectName(QString::fromUtf8("GroupBox"));
        gridLayout = new QGridLayout(GroupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(GroupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setLayoutDirection(Qt::LeftToRight);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        interface_box = new QComboBox(GroupBox);
        interface_box->setObjectName(QString::fromUtf8("interface_box"));

        gridLayout->addWidget(interface_box, 0, 1, 1, 5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 6, 1, 1);

        label_6 = new QLabel(GroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_6, 1, 0, 1, 1);

        to_mac_edit = new QLineEdit(GroupBox);
        to_mac_edit->setObjectName(QString::fromUtf8("to_mac_edit"));

        gridLayout->addWidget(to_mac_edit, 1, 1, 1, 1);

        label_7 = new QLabel(GroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 2, 1, 1);

        from_mac_edit = new QLineEdit(GroupBox);
        from_mac_edit->setObjectName(QString::fromUtf8("from_mac_edit"));

        gridLayout->addWidget(from_mac_edit, 1, 3, 1, 1);

        label_9 = new QLabel(GroupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 1, 4, 1, 1);

        protocol_box = new QComboBox(GroupBox);
        protocol_box->setObjectName(QString::fromUtf8("protocol_box"));

        gridLayout->addWidget(protocol_box, 1, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 6, 1, 1);


        gridLayout_2->addWidget(GroupBox, 0, 0, 1, 4);


        retranslateUi(EthernetWidget);

        QMetaObject::connectSlotsByName(EthernetWidget);
    } // setupUi

    void retranslateUi(QWidget *EthernetWidget)
    {
        EthernetWidget->setWindowTitle(QApplication::translate("EthernetWidget", "EthernetWidget", 0, QApplication::UnicodeUTF8));
        GroupBox->setTitle(QApplication::translate("EthernetWidget", "Ethernet", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("EthernetWidget", "Interface", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("EthernetWidget", "MAC(To)", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("EthernetWidget", "MAC(From)", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("EthernetWidget", "Protocol", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EthernetWidget: public Ui_EthernetWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ETHERNET_WIDGET_H
