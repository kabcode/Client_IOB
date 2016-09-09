/********************************************************************************
** Form generated from reading UI file 'client_iob.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_IOB_H
#define UI_CLIENT_IOB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client_IOBClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client_IOBClass)
    {
        if (Client_IOBClass->objectName().isEmpty())
            Client_IOBClass->setObjectName(QStringLiteral("Client_IOBClass"));
        Client_IOBClass->resize(600, 400);
        menuBar = new QMenuBar(Client_IOBClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Client_IOBClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client_IOBClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Client_IOBClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Client_IOBClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Client_IOBClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Client_IOBClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client_IOBClass->setStatusBar(statusBar);

        retranslateUi(Client_IOBClass);

        QMetaObject::connectSlotsByName(Client_IOBClass);
    } // setupUi

    void retranslateUi(QMainWindow *Client_IOBClass)
    {
        Client_IOBClass->setWindowTitle(QApplication::translate("Client_IOBClass", "Client_IOB", 0));
    } // retranslateUi

};

namespace Ui {
    class Client_IOBClass: public Ui_Client_IOBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_IOB_H
