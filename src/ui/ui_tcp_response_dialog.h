/********************************************************************************
** Form generated from reading UI file 'tcp_response_dialog.ui'
**
** Created: Mon Dec 17 16:02:57 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCP_RESPONSE_DIALOG_H
#define UI_TCP_RESPONSE_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_TcpReponseDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *close_button;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *layout;
    QLabel *tip_label;

    void setupUi(QDialog *TcpReponseDialog)
    {
        if (TcpReponseDialog->objectName().isEmpty())
            TcpReponseDialog->setObjectName(QString::fromUtf8("TcpReponseDialog"));
        TcpReponseDialog->resize(400, 300);
        gridLayout = new QGridLayout(TcpReponseDialog);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        close_button = new QPushButton(TcpReponseDialog);
        close_button->setObjectName(QString::fromUtf8("close_button"));

        gridLayout->addWidget(close_button, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        layout = new QHBoxLayout();
        layout->setSpacing(6);
        layout->setObjectName(QString::fromUtf8("layout"));

        gridLayout->addLayout(layout, 0, 0, 1, 3);

        tip_label = new QLabel(TcpReponseDialog);
        tip_label->setObjectName(QString::fromUtf8("tip_label"));

        gridLayout->addWidget(tip_label, 1, 0, 1, 1);


        retranslateUi(TcpReponseDialog);

        QMetaObject::connectSlotsByName(TcpReponseDialog);
    } // setupUi

    void retranslateUi(QDialog *TcpReponseDialog)
    {
        TcpReponseDialog->setWindowTitle(QApplication::translate("TcpReponseDialog", "TcpReponseDialog", 0, QApplication::UnicodeUTF8));
        close_button->setText(QApplication::translate("TcpReponseDialog", "Close", 0, QApplication::UnicodeUTF8));
        tip_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TcpReponseDialog: public Ui_TcpReponseDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCP_RESPONSE_DIALOG_H
