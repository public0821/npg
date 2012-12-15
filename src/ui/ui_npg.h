/********************************************************************************
** Form generated from reading UI file 'npg.ui'
**
** Created: Sat Dec 15 17:25:45 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NPG_H
#define UI_NPG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_npgClass
{
public:
    QAction *action_test;
    QAction *action_quit;
    QAction *action_tool_hex;
    QAction *action_tool_ip;
    QAction *action_tool_time;
    QAction *action_tool_base64;
    QAction *action_about;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuTool;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *npgClass)
    {
        if (npgClass->objectName().isEmpty())
            npgClass->setObjectName(QString::fromUtf8("npgClass"));
        npgClass->resize(794, 600);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(npgClass->sizePolicy().hasHeightForWidth());
        npgClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/npg/npg"), QSize(), QIcon::Normal, QIcon::Off);
        npgClass->setWindowIcon(icon);
        action_test = new QAction(npgClass);
        action_test->setObjectName(QString::fromUtf8("action_test"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/npg/category_add"), QSize(), QIcon::Normal, QIcon::Off);
        action_test->setIcon(icon1);
        action_test->setShortcutContext(Qt::ApplicationShortcut);
        action_test->setIconVisibleInMenu(true);
        action_quit = new QAction(npgClass);
        action_quit->setObjectName(QString::fromUtf8("action_quit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/npg/category_delete"), QSize(), QIcon::Normal, QIcon::Off);
        action_quit->setIcon(icon2);
        action_quit->setIconVisibleInMenu(true);
        action_tool_hex = new QAction(npgClass);
        action_tool_hex->setObjectName(QString::fromUtf8("action_tool_hex"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/npg/field_hex"), QSize(), QIcon::Normal, QIcon::Off);
        action_tool_hex->setIcon(icon3);
        action_tool_ip = new QAction(npgClass);
        action_tool_ip->setObjectName(QString::fromUtf8("action_tool_ip"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/npg/field_ip"), QSize(), QIcon::Normal, QIcon::Off);
        action_tool_ip->setIcon(icon4);
        action_tool_time = new QAction(npgClass);
        action_tool_time->setObjectName(QString::fromUtf8("action_tool_time"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/npg/field_time"), QSize(), QIcon::Normal, QIcon::Off);
        action_tool_time->setIcon(icon5);
        action_tool_base64 = new QAction(npgClass);
        action_tool_base64->setObjectName(QString::fromUtf8("action_tool_base64"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/npg/field_base64"), QSize(), QIcon::Normal, QIcon::Off);
        action_tool_base64->setIcon(icon6);
        action_about = new QAction(npgClass);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/npg/about"), QSize(), QIcon::Normal, QIcon::Off);
        action_about->setIcon(icon7);
        centralwidget = new QWidget(npgClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        npgClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(npgClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 794, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuTool = new QMenu(menubar);
        menuTool->setObjectName(QString::fromUtf8("menuTool"));
        npgClass->setMenuBar(menubar);
        statusbar = new QStatusBar(npgClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        npgClass->setStatusBar(statusbar);
        toolBar = new QToolBar(npgClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setContextMenuPolicy(Qt::NoContextMenu);
        toolBar->setMovable(false);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        npgClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTool->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(action_quit);
        menuHelp->addAction(action_about);
        menuTool->addAction(action_tool_hex);
        menuTool->addAction(action_tool_ip);
        menuTool->addAction(action_tool_time);
        menuTool->addAction(action_tool_base64);
        toolBar->addSeparator();

        retranslateUi(npgClass);

        QMetaObject::connectSlotsByName(npgClass);
    } // setupUi

    void retranslateUi(QMainWindow *npgClass)
    {
        npgClass->setWindowTitle(QApplication::translate("npgClass", "Network Packet Generator", 0, QApplication::UnicodeUTF8));
        action_test->setText(QApplication::translate("npgClass", "New(&N)", 0, QApplication::UnicodeUTF8));
        action_test->setShortcut(QApplication::translate("npgClass", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        action_quit->setText(QApplication::translate("npgClass", "Quit(&Q)", 0, QApplication::UnicodeUTF8));
        action_quit->setShortcut(QApplication::translate("npgClass", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_tool_hex->setText(QApplication::translate("npgClass", "Hex", 0, QApplication::UnicodeUTF8));
        action_tool_ip->setText(QApplication::translate("npgClass", "IP", 0, QApplication::UnicodeUTF8));
        action_tool_time->setText(QApplication::translate("npgClass", "Time", 0, QApplication::UnicodeUTF8));
        action_tool_base64->setText(QApplication::translate("npgClass", "Base64", 0, QApplication::UnicodeUTF8));
        action_about->setText(QApplication::translate("npgClass", "About", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("npgClass", "File(&F)", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("npgClass", "Help(&H)", 0, QApplication::UnicodeUTF8));
        menuTool->setTitle(QApplication::translate("npgClass", "Tool(&T)", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("npgClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class npgClass: public Ui_npgClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NPG_H
