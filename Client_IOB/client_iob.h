#ifndef CLIENT_IOB_H
#define CLIENT_IOB_H

#include <QtWidgets/QMainWindow>
#include "ui_client_iob.h"
// qt network library
#include <QtNetwork>
// Library for processing XML documents
#include <QDomDocument>
#include <QXMLStreamReader>
// Library for file processing
#include <QFile>
#include <QFileInfo>
// Library for message boxes
#include <QMessageBox>
#include <QInputDialog>
// library for menu icon
#include <QSystemTrayIcon>
#include <QMenu>

//**************//
// Client Class //
//************* //

class Client_IOB : public QMainWindow
{
	Q_OBJECT

public:
	Client_IOB(QWidget *parent = 0);
	~Client_IOB();
	enum STATUS
	{
		AVAILABE,
		BUSY,
		ABSENT
	};

private slots:
	void updateMember();
	void updateStatus(int);

private:
	// member variables
	QString      mXMLFileName = "client.xml";
	QDomDocument mStatusXML;
	int          mID;
	QString      mName;
	int          mStatus;
	QString      mLocation;
	QString      mPhone;
	QString      mNotes;
	
	// network variables
	QTcpSocket      *mTCPSocket;
	QNetworkSession *mNetworkSession;
	
	// private functions
	QDomDocument loadXMLDocument(QString);
	void		 writeXMLDocument();
	void         setStatus(QDomDocument);
	void         contactServer(QTcpSocket*);


	// UI variables
	Ui::Client_IOBClass ui;

	QLineEdit *locationEdit   = 0;
	QLineEdit *phoneEdit      = 0;
	QLineEdit *notesEdit      = 0;
	QPushButton *updateButton = 0;

	QPushButton *buttonRed      = 0;
	QPushButton *buttonYellow   = 0;
	QPushButton *buttonGreen    = 0;
	QSignalMapper *signalMapper = 0;

	QSystemTrayIcon *trayIcon = 0;
	QMenu *trayIconMenu       = 0;
	QAction *minimizeAction;
	QAction *restoreAction;
	QAction *quitAction;

	// UI functions
	void initializeUIComponents();
	void createMenuTrayActions();
};

#endif // CLIENT_IOB_H
