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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client_IOBClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *statuEdit;
    QPushButton *updateButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *idLabel;
    QLabel *nameLabel;
    QLabel *statusLabel;
    QMenuBar *menuBar;
    QMenu *menuClient_InOutBoard;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client_IOBClass)
    {
        if (Client_IOBClass->objectName().isEmpty())
            Client_IOBClass->setObjectName(QStringLiteral("Client_IOBClass"));
        Client_IOBClass->resize(600, 400);
        centralWidget = new QWidget(Client_IOBClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 89, 521, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        idEdit = new QLineEdit(horizontalLayoutWidget);
        idEdit->setObjectName(QStringLiteral("idEdit"));

        horizontalLayout->addWidget(idEdit);

        nameEdit = new QLineEdit(horizontalLayoutWidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        horizontalLayout->addWidget(nameEdit);

        statuEdit = new QLineEdit(horizontalLayoutWidget);
        statuEdit->setObjectName(QStringLiteral("statuEdit"));

        horizontalLayout->addWidget(statuEdit);

        updateButton = new QPushButton(horizontalLayoutWidget);
        updateButton->setObjectName(QStringLiteral("updateButton"));

        horizontalLayout->addWidget(updateButton);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(30, 70, 441, 21));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        idLabel = new QLabel(horizontalLayoutWidget_2);
        idLabel->setObjectName(QStringLiteral("idLabel"));

        horizontalLayout_2->addWidget(idLabel);

        nameLabel = new QLabel(horizontalLayoutWidget_2);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        horizontalLayout_2->addWidget(nameLabel);

        statusLabel = new QLabel(horizontalLayoutWidget_2);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));

        horizontalLayout_2->addWidget(statusLabel);

        Client_IOBClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Client_IOBClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuClient_InOutBoard = new QMenu(menuBar);
        menuClient_InOutBoard->setObjectName(QStringLiteral("menuClient_InOutBoard"));
        Client_IOBClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Client_IOBClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Client_IOBClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Client_IOBClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client_IOBClass->setStatusBar(statusBar);

        menuBar->addAction(menuClient_InOutBoard->menuAction());

        retranslateUi(Client_IOBClass);

        QMetaObject::connectSlotsByName(Client_IOBClass);
    } // setupUi

    void retranslateUi(QMainWindow *Client_IOBClass)
    {
        Client_IOBClass->setWindowTitle(QApplication::translate("Client_IOBClass", "Client - InOutBoard", 0));
        updateButton->setText(QApplication::translate("Client_IOBClass", "Update", 0));
        idLabel->setText(QApplication::translate("Client_IOBClass", "ID", 0));
        nameLabel->setText(QApplication::translate("Client_IOBClass", "Name", 0));
        statusLabel->setText(QApplication::translate("Client_IOBClass", "Status", 0));
        menuClient_InOutBoard->setTitle(QApplication::translate("Client_IOBClass", "Men\303\274", 0));
    } // retranslateUi

};

namespace Ui {
    class Client_IOBClass: public Ui_Client_IOBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_IOB_H
