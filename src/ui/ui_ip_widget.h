/********************************************************************************
** Form generated from reading UI file 'ip_widget.ui'
**
** Created: Fri Dec 14 15:18:32 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IP_WIDGET_H
#define UI_IP_WIDGET_H

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

class Ui_IpWidget
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QComboBox *protocol_box;
    QLineEdit *ip_edit;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *IpWidget)
    {
        if (IpWidget->objectName().isEmpty())
            IpWidget->setObjectName(QString::fromUtf8("IpWidget"));
        IpWidget->resize(226, 46);
        gridLayout = new QGridLayout(IpWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(IpWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 1, -1, -1);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_2, 0, 2, 1, 1);

        protocol_box = new QComboBox(groupBox);
        protocol_box->setObjectName(QString::fromUtf8("protocol_box"));

        gridLayout_2->addWidget(protocol_box, 0, 3, 1, 1);

        ip_edit = new QLineEdit(groupBox);
        ip_edit->setObjectName(QString::fromUtf8("ip_edit"));

        gridLayout_2->addWidget(ip_edit, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 4, 1, 1);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(IpWidget);

        QMetaObject::connectSlotsByName(IpWidget);
    } // setupUi

    void retranslateUi(QWidget *IpWidget)
    {
        IpWidget->setWindowTitle(QApplication::translate("IpWidget", "IpWidget", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("IpWidget", "IP", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("IpWidget", "IP:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("IpWidget", "Protocol:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IpWidget: public Ui_IpWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IP_WIDGET_H
