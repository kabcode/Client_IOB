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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client_IOBClass
{
public:
    QWidget *centralWidget;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QPushButton *buttonAbsent;
    QSpacerItem *verticalSpacer;
    QPushButton *buttonBusy;
    QSpacerItem *verticalSpacer_2;
    QPushButton *buttonAvailable;
    QTableView *tableView;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEditPhone;
    QPushButton *pushButtonUpdate;
    QLineEdit *lineEditLocation;
    QLabel *labelNotes;
    QLabel *labelLocation;
    QLineEdit *lineEditNotes;
    QLabel *labelPhone;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Client_IOBClass)
    {
        if (Client_IOBClass->objectName().isEmpty())
            Client_IOBClass->setObjectName(QStringLiteral("Client_IOBClass"));
        Client_IOBClass->resize(639, 406);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Client_IOBClass->sizePolicy().hasHeightForWidth());
        Client_IOBClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(Client_IOBClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 0, 601, 311));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        buttonAbsent = new QPushButton(horizontalLayoutWidget_3);
        buttonAbsent->setObjectName(QStringLiteral("buttonAbsent"));
        sizePolicy.setHeightForWidth(buttonAbsent->sizePolicy().hasHeightForWidth());
        buttonAbsent->setSizePolicy(sizePolicy);
        buttonAbsent->setMinimumSize(QSize(75, 75));
        buttonAbsent->setMaximumSize(QSize(16777215, 16777215));
        buttonAbsent->setBaseSize(QSize(0, 0));
        buttonAbsent->setAutoFillBackground(false);
        buttonAbsent->setStyleSheet(QLatin1String("border: none;\n"
"background: none;"));
        buttonAbsent->setIconSize(QSize(75, 75));
        buttonAbsent->setCheckable(false);
        buttonAbsent->setChecked(false);

        verticalLayout->addWidget(buttonAbsent);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        buttonBusy = new QPushButton(horizontalLayoutWidget_3);
        buttonBusy->setObjectName(QStringLiteral("buttonBusy"));
        sizePolicy.setHeightForWidth(buttonBusy->sizePolicy().hasHeightForWidth());
        buttonBusy->setSizePolicy(sizePolicy);
        buttonBusy->setMinimumSize(QSize(75, 75));
        buttonBusy->setStyleSheet(QLatin1String("border: none;\n"
"background: none;"));
        buttonBusy->setIconSize(QSize(75, 75));

        verticalLayout->addWidget(buttonBusy);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        buttonAvailable = new QPushButton(horizontalLayoutWidget_3);
        buttonAvailable->setObjectName(QStringLiteral("buttonAvailable"));
        sizePolicy.setHeightForWidth(buttonAvailable->sizePolicy().hasHeightForWidth());
        buttonAvailable->setSizePolicy(sizePolicy);
        buttonAvailable->setMinimumSize(QSize(75, 75));
        buttonAvailable->setStyleSheet(QLatin1String("border: none;\n"
"background: none;"));
        buttonAvailable->setIconSize(QSize(75, 75));

        verticalLayout->addWidget(buttonAvailable);


        horizontalLayout_3->addLayout(verticalLayout);

        tableView = new QTableView(horizontalLayoutWidget_3);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout_3->addWidget(tableView);

        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 320, 601, 51));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEditPhone = new QLineEdit(gridLayoutWidget);
        lineEditPhone->setObjectName(QStringLiteral("lineEditPhone"));

        gridLayout->addWidget(lineEditPhone, 2, 2, 1, 1);

        pushButtonUpdate = new QPushButton(gridLayoutWidget);
        pushButtonUpdate->setObjectName(QStringLiteral("pushButtonUpdate"));

        gridLayout->addWidget(pushButtonUpdate, 2, 3, 1, 1);

        lineEditLocation = new QLineEdit(gridLayoutWidget);
        lineEditLocation->setObjectName(QStringLiteral("lineEditLocation"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditLocation->sizePolicy().hasHeightForWidth());
        lineEditLocation->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditLocation, 2, 0, 1, 1);

        labelNotes = new QLabel(gridLayoutWidget);
        labelNotes->setObjectName(QStringLiteral("labelNotes"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(labelNotes->sizePolicy().hasHeightForWidth());
        labelNotes->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(labelNotes, 0, 2, 1, 1);

        labelLocation = new QLabel(gridLayoutWidget);
        labelLocation->setObjectName(QStringLiteral("labelLocation"));
        sizePolicy.setHeightForWidth(labelLocation->sizePolicy().hasHeightForWidth());
        labelLocation->setSizePolicy(sizePolicy);

        gridLayout->addWidget(labelLocation, 0, 0, 1, 1);

        lineEditNotes = new QLineEdit(gridLayoutWidget);
        lineEditNotes->setObjectName(QStringLiteral("lineEditNotes"));
        sizePolicy1.setHeightForWidth(lineEditNotes->sizePolicy().hasHeightForWidth());
        lineEditNotes->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEditNotes, 2, 1, 1, 1);

        labelPhone = new QLabel(gridLayoutWidget);
        labelPhone->setObjectName(QStringLiteral("labelPhone"));

        gridLayout->addWidget(labelPhone, 0, 1, 1, 1);

        Client_IOBClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Client_IOBClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Client_IOBClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Client_IOBClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Client_IOBClass->setStatusBar(statusBar);

        retranslateUi(Client_IOBClass);

        QMetaObject::connectSlotsByName(Client_IOBClass);
    } // setupUi

    void retranslateUi(QMainWindow *Client_IOBClass)
    {
        Client_IOBClass->setWindowTitle(QApplication::translate("Client_IOBClass", "Client - InOutBoard", 0));
        buttonAbsent->setText(QString());
        buttonBusy->setText(QString());
        buttonAvailable->setText(QString());
        pushButtonUpdate->setText(QApplication::translate("Client_IOBClass", "Update", 0));
        labelNotes->setText(QApplication::translate("Client_IOBClass", "Notes", 0));
        labelLocation->setText(QApplication::translate("Client_IOBClass", "Location", 0));
        labelPhone->setText(QApplication::translate("Client_IOBClass", "Phone", 0));
    } // retranslateUi

};

namespace Ui {
    class Client_IOBClass: public Ui_Client_IOBClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_IOB_H
