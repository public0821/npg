/********************************************************************************
** Form generated from reading UI file 'protocol_widget.ui'
**
** Created: Sat Dec 15 17:25:45 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOCOL_WIDGET_H
#define UI_PROTOCOL_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include "widget/protocol_tree.h"

QT_BEGIN_NAMESPACE

class Ui_ProtocolWidgetClass
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *advanced_layout;
    ProtocolTree *treeWidget;
    QHBoxLayout *protocol_layout;
    QPushButton *load_config_button;
    QPushButton *save_config_button;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *ProtocolWidgetClass)
    {
        if (ProtocolWidgetClass->objectName().isEmpty())
            ProtocolWidgetClass->setObjectName(QString::fromUtf8("ProtocolWidgetClass"));
        ProtocolWidgetClass->resize(394, 324);
        gridLayout_2 = new QGridLayout(ProtocolWidgetClass);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        advanced_layout = new QHBoxLayout();
        advanced_layout->setObjectName(QString::fromUtf8("advanced_layout"));

        gridLayout_2->addLayout(advanced_layout, 6, 0, 1, 3);

        treeWidget = new ProtocolTree(ProtocolWidgetClass);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFrameShape(QFrame::StyledPanel);
        treeWidget->setFrameShadow(QFrame::Sunken);
        treeWidget->setLineWidth(0);
        treeWidget->setMidLineWidth(0);
        treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidget->header()->setHighlightSections(true);

        gridLayout_2->addWidget(treeWidget, 1, 0, 1, 3);

        protocol_layout = new QHBoxLayout();
        protocol_layout->setObjectName(QString::fromUtf8("protocol_layout"));

        gridLayout_2->addLayout(protocol_layout, 0, 0, 1, 3);

        load_config_button = new QPushButton(ProtocolWidgetClass);
        load_config_button->setObjectName(QString::fromUtf8("load_config_button"));

        gridLayout_2->addWidget(load_config_button, 3, 0, 1, 1);

        save_config_button = new QPushButton(ProtocolWidgetClass);
        save_config_button->setObjectName(QString::fromUtf8("save_config_button"));

        gridLayout_2->addWidget(save_config_button, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 2, 1, 1);


        retranslateUi(ProtocolWidgetClass);

        QMetaObject::connectSlotsByName(ProtocolWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *ProtocolWidgetClass)
    {
        ProtocolWidgetClass->setWindowTitle(QApplication::translate("ProtocolWidgetClass", "Form", 0, QApplication::UnicodeUTF8));
        load_config_button->setText(QApplication::translate("ProtocolWidgetClass", "Load", 0, QApplication::UnicodeUTF8));
        save_config_button->setText(QApplication::translate("ProtocolWidgetClass", "Save", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProtocolWidgetClass: public Ui_ProtocolWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOL_WIDGET_H
