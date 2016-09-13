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

public slots:
	void updateMember();

private:
	// member variables
	QString      mXMLFileName = "client.xml";
	QDomDocument mStatusXML;
	int          mID;
	QString      mName;
	int          mStatus;
	
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

	QLineEdit *idEdit = 0;
	QLineEdit *nameEdit   = 0;
	QLineEdit *statusEdit = 0;

	QPushButton *updateButton = 0;

	// UI functions
	void initializeUIComponents();
};

#endif // CLIENT_IOB_H
