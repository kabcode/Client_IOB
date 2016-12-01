#ifndef CLIENT_IOB_H
#define CLIENT_IOB_H

// standard includes 
#include <QtWidgets/QMainWindow>
#include "ui_client_iob.h"
// qt network library
#include <QtNetwork>
// qt web socket lib
#include <QtWebSockets>
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

//******************//
//   Client Class   //
//******************//

class Client_IOB : public QMainWindow
{
	Q_OBJECT

public:
	Client_IOB(QWidget *parent = 0);
	~Client_IOB();
	
	// client status
	enum STATUS
	{
		AVAILABE,
		BUSY,
		ABSENT
	};

	// message control
	enum MESSAGEID
	{
		REQUEST,
		REGISTRATION,
		UPDATE,
		MESSAGE,
		REFUSAL,
		CLOSING,
		TEST
	};

signals:
	

private slots:
	// update the internal member variables
	void updateMember();
	// update the visible status
	void updateStatus(int);
	// network slots
	void onConnected();
	void onTextMessageReceived(QString);
	void closed();
	void closingConnection();
	void sendUpdate();

private:
	// member variables
	QString      mXMLFileName = "client.xml";
	QDomDocument mStatusXML;
	QUuid        mID;
	QString      mName;
	int          mStatus;
	QString      mLocation;
	QString      mPhone;
	QString      mNotes;
	QHostAddress mServerAddress;
	qint16		 mServerPort;
	
	// network variables
	QWebSocket		mWebSocket;
	QUrl			 mUrl;
	
	// private functions
	void loadXMLDocument();
	void writeXMLDocument();
	void setStatus();
	void contactServer();
	void registerAtServer();
	QString buildMessageBody(QString);

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

	QSharedPointer<QSystemTrayIcon> trayIcon;
	QMenu *trayIconMenu       = 0;
	QAction *minimizeAction   = 0;
	QAction *restoreAction    = 0; 
	QAction *quitAction       = 0;

	// UI functions
	void initializeUIComponents();
	void createMenuTrayActions();
};

#endif // CLIENT_IOB_H
