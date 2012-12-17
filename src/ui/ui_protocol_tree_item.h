/********************************************************************************
** Form generated from reading UI file 'protocol_tree_item.ui'
**
** Created: Mon Dec 17 16:02:57 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROTOCOL_TREE_ITEM_H
#define UI_PROTOCOL_TREE_ITEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProtocolTreeItem
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *layout;

    void setupUi(QWidget *ProtocolTreeItem)
    {
        if (ProtocolTreeItem->objectName().isEmpty())
            ProtocolTreeItem->setObjectName(QString::fromUtf8("ProtocolTreeItem"));
        ProtocolTreeItem->resize(80, 20);
        gridLayout_2 = new QGridLayout(ProtocolTreeItem);
        gridLayout_2->setSpacing(1);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, 1, 9, 1);
        layout = new QGridLayout();
        layout->setSpacing(6);
        layout->setObjectName(QString::fromUtf8("layout"));

        gridLayout_2->addLayout(layout, 0, 0, 1, 1);


        retranslateUi(ProtocolTreeItem);

        QMetaObject::connectSlotsByName(ProtocolTreeItem);
    } // setupUi

    void retranslateUi(QWidget *ProtocolTreeItem)
    {
        ProtocolTreeItem->setWindowTitle(QApplication::translate("ProtocolTreeItem", "ProtocolTreeItem", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProtocolTreeItem: public Ui_ProtocolTreeItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROTOCOL_TREE_ITEM_H
