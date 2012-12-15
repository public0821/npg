/********************************************************************************
** Form generated from reading UI file 'converter_dialog.ui'
**
** Created: Sat Dec 15 17:25:45 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONVERTER_DIALOG_H
#define UI_CONVERTER_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ConverterDialog
{
public:
    QGridLayout *gridLayout;
    QTextEdit *from_edit;
    QLabel *from_label;
    QLabel *to_label;
    QTextEdit *to_edit;
    QPushButton *revert_button;
    QPushButton *convert_button;

    void setupUi(QDialog *ConverterDialog)
    {
        if (ConverterDialog->objectName().isEmpty())
            ConverterDialog->setObjectName(QString::fromUtf8("ConverterDialog"));
        ConverterDialog->resize(234, 177);
        gridLayout = new QGridLayout(ConverterDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        from_edit = new QTextEdit(ConverterDialog);
        from_edit->setObjectName(QString::fromUtf8("from_edit"));

        gridLayout->addWidget(from_edit, 0, 1, 1, 2);

        from_label = new QLabel(ConverterDialog);
        from_label->setObjectName(QString::fromUtf8("from_label"));
        from_label->setLayoutDirection(Qt::LeftToRight);
        from_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(from_label, 0, 0, 1, 1);

        to_label = new QLabel(ConverterDialog);
        to_label->setObjectName(QString::fromUtf8("to_label"));
        to_label->setLayoutDirection(Qt::LeftToRight);
        to_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(to_label, 2, 0, 1, 1);

        to_edit = new QTextEdit(ConverterDialog);
        to_edit->setObjectName(QString::fromUtf8("to_edit"));

        gridLayout->addWidget(to_edit, 2, 1, 1, 2);

        revert_button = new QPushButton(ConverterDialog);
        revert_button->setObjectName(QString::fromUtf8("revert_button"));

        gridLayout->addWidget(revert_button, 1, 2, 1, 1);

        convert_button = new QPushButton(ConverterDialog);
        convert_button->setObjectName(QString::fromUtf8("convert_button"));

        gridLayout->addWidget(convert_button, 1, 1, 1, 1);


        retranslateUi(ConverterDialog);

        QMetaObject::connectSlotsByName(ConverterDialog);
    } // setupUi

    void retranslateUi(QDialog *ConverterDialog)
    {
        ConverterDialog->setWindowTitle(QApplication::translate("ConverterDialog", "ConverterDialog", 0, QApplication::UnicodeUTF8));
        from_label->setText(QApplication::translate("ConverterDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        to_label->setText(QApplication::translate("ConverterDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        revert_button->setText(QApplication::translate("ConverterDialog", "Revert", 0, QApplication::UnicodeUTF8));
        convert_button->setText(QApplication::translate("ConverterDialog", "Convert", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConverterDialog: public Ui_ConverterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONVERTER_DIALOG_H
