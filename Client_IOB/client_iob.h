#ifndef CLIENT_IOB_H
#define CLIENT_IOB_H

#include <QtWidgets/QMainWindow>
#include "ui_client_iob.h"
// Library for processing XML documents
#include <QDomDocument>
#include <QXMLStreamReader>
// Library for file processing
#include <QFile>
#include <QFileInfo>
// Library for message boxes
#include <QMessageBox>
// own includes
#include "Client_User.h"

//**************//
// Client Class //
//************* //

class Client_IOB : public QMainWindow
{
	Q_OBJECT

public:
	Client_IOB(QWidget *parent = 0);
	~Client_IOB();

private:
	
	QString mXMLFileName;
	QDomDocument mStatusXML; // own status update
	Client_User mUser;

	// private functions
	QDomDocument Client_IOB::loadXMLDocument(QString);

	Ui::Client_IOBClass ui;
};

#endif // CLIENT_IOB_H
