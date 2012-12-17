/********************************************************************************
** Form generated from reading UI file 'field_select_dialog.ui'
**
** Created: Mon Dec 17 11:38:33 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIELD_SELECT_DIALOG_H
#define UI_FIELD_SELECT_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_FieldSelectDialog
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *tree_widget;
    QPushButton *ok_button;
    QPushButton *cancel_button;
    QSpacerItem *horizontalSpacer;
    QCheckBox *select_all_checkbox;

    void setupUi(QDialog *FieldSelectDialog)
    {
        if (FieldSelectDialog->objectName().isEmpty())
            FieldSelectDialog->setObjectName(QString::fromUtf8("FieldSelectDialog"));
        FieldSelectDialog->resize(400, 300);
        gridLayout = new QGridLayout(FieldSelectDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tree_widget = new QTreeWidget(FieldSelectDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        tree_widget->setHeaderItem(__qtreewidgetitem);
        tree_widget->setObjectName(QString::fromUtf8("tree_widget"));

        gridLayout->addWidget(tree_widget, 0, 0, 1, 4);

        ok_button = new QPushButton(FieldSelectDialog);
        ok_button->setObjectName(QString::fromUtf8("ok_button"));

        gridLayout->addWidget(ok_button, 1, 2, 1, 1);

        cancel_button = new QPushButton(FieldSelectDialog);
        cancel_button->setObjectName(QString::fromUtf8("cancel_button"));

        gridLayout->addWidget(cancel_button, 1, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        select_all_checkbox = new QCheckBox(FieldSelectDialog);
        select_all_checkbox->setObjectName(QString::fromUtf8("select_all_checkbox"));

        gridLayout->addWidget(select_all_checkbox, 1, 0, 1, 1);


        retranslateUi(FieldSelectDialog);

        QMetaObject::connectSlotsByName(FieldSelectDialog);
    } // setupUi

    void retranslateUi(QDialog *FieldSelectDialog)
    {
        FieldSelectDialog->setWindowTitle(QApplication::translate("FieldSelectDialog", "FieldSelectDialog", 0, QApplication::UnicodeUTF8));
        ok_button->setText(QApplication::translate("FieldSelectDialog", "PushButton", 0, QApplication::UnicodeUTF8));
        cancel_button->setText(QApplication::translate("FieldSelectDialog", "PushButton", 0, QApplication::UnicodeUTF8));
        select_all_checkbox->setText(QApplication::translate("FieldSelectDialog", "checkbox", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FieldSelectDialog: public Ui_FieldSelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIELD_SELECT_DIALOG_H
