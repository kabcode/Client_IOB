#include "client_iob.h"

//******************//
//   Client Class   //
//******************//

// constructor
Client_IOB::Client_IOB(QWidget *parent)
	: QMainWindow(parent),
	mStatusXML("status")
{

	// load xml document with last status
	this->loadXMLDocument();
		
	// set status based on xml document
	this->setStatus();
		
	// contact server
	this->contactServer();
	
	// set UI
	ui.setupUi(this);
	this->initializeUIComponents();
	
} // END constructor

// destructor
Client_IOB::~Client_IOB()
{
	writeXMLDocument();
	closingConnection();
	delete trayIconMenu;
	delete signalMapper;	
} // END destructor

  // load the XML document
void Client_IOB::loadXMLDocument()
{
	// check if client list exist
	QFile file(mXMLFileName);
	QFileInfo checkFile(file);
	if (!checkFile.exists() && !checkFile.isFile())
	{
		// create a new xml document
		if (file.open(QIODevice::WriteOnly))
		{
			// write a new XML document for an unkown user
			QXmlStreamWriter xmlWriter(&file);
			xmlWriter.setAutoFormatting(true);
			xmlWriter.writeStartDocument();
			xmlWriter.writeStartElement("client");
			xmlWriter.writeAttribute(QString("id"), QUuid::createUuid().toString());
			xmlWriter.writeTextElement(QString("name"), "");
			xmlWriter.writeTextElement(QString("status"), QString::number(Client_IOB::STATUS::ABSENT));
			xmlWriter.writeEndElement();
			xmlWriter.writeEndDocument();
			file.close();
		}
		// show error message box and exit the app
		else
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", "Not allowed to create file!");
			messageBox.setFixedSize(500, 200);
			QApplication::exit(EXIT_FAILURE);
		}
	}
	
	// if the file cant be read
	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Unable to read XML file!!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}
	// content is not correct
	if (!mStatusXML.setContent(&file))
	{
		file.close();
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "File contains wrong content!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}
} // END loadXMLDocument

// fill the member variables with the content of the xml document
void Client_IOB::setStatus()
{
	// get the value of the document nodes
	QDomElement root = mStatusXML.firstChildElement("client");
	mID = root.attribute("id");
	if (mID == QUuid::QUuid().toString())
	{
		mID = QUuid::createUuid();
	}
		
	qDebug() << mID;
	QDomElement domStatus = root.firstChildElement("status");
	mStatus = domStatus.text().toInt();
	qDebug() << mStatus;
	QDomElement domName = root.firstChildElement("name");
	// if the name tag is empty ask for user name
	if (domName.text().isEmpty())
	{
		bool ok;
		QString text = QInputDialog::getText(this, tr("Please provide a user name."),
			tr("User name:"), QLineEdit::Normal, "" , &ok);
		
		// check if name is provided
		if (ok && !text.isEmpty())
		{
			mName = text;
		}
		// if user does not provide a name
		else
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", "No name provided!");
			messageBox.setFixedSize(500, 200);
			QApplication::exit(EXIT_FAILURE);
		}	
	}
	else
	{ 
		mName = domName.text();
	}
	qDebug() << mName;
	QDomElement domLocation = root.firstChildElement("location");
	mLocation = domLocation.text();
	qDebug() << mLocation;
	QDomElement domPhone = root.firstChildElement("phone");
	mPhone = domPhone.text();
	qDebug() << mPhone;
	QDomElement domNotes = root.firstChildElement("notes");
	mNotes = domNotes.text();
	qDebug() << mNotes;

}// END setStatus

// setup the ui components
void Client_IOB::initializeUIComponents()
{
	// set title
	QString mainWinwdowTitle = QString("%1 - InOutBoard").arg(mName);
	this->setWindowTitle(mainWinwdowTitle);
	this->setWindowIcon(QIcon("Resources/kicker.ico"));
	this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
	this->setFixedSize(639, 406);

	// setup editable lines
	this->locationEdit = ui.lineEditLocation;
	this->locationEdit->setText(mLocation);
	this->phoneEdit = ui.lineEditPhone;
	this->phoneEdit->setText(mPhone);
	this->notesEdit = ui.lineEditNotes;
	this->notesEdit->setText(mNotes);

	// connect update button and update function
	this->updateButton = ui.pushButtonUpdate;
	connect(this->updateButton, SIGNAL(clicked()), this, SLOT(updateMember()));

	// push buttons for status update
	buttonRed    = ui.buttonAbsent;
	buttonYellow = ui.buttonBusy;
	buttonGreen  = ui.buttonAvailable;
	signalMapper = new QSignalMapper(this);
	signalMapper->setMapping(buttonRed,    STATUS::ABSENT);
	signalMapper->setMapping(buttonYellow, STATUS::BUSY);
	signalMapper->setMapping(buttonGreen,  STATUS::AVAILABE);
	connect(buttonRed,    SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(buttonYellow, SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(buttonGreen,  SIGNAL(clicked()), signalMapper, SLOT(map()));
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(updateStatus(int)));
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(sendUpdate()));
	updateStatus(mStatus);

	// set tray icon settings
	trayIconMenu = new QMenu(this);
	createMenuTrayActions();
	trayIconMenu->addAction(minimizeAction);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);
	trayIcon = QSharedPointer<QSystemTrayIcon>(new QSystemTrayIcon(this));
	QIcon icon = QIcon("Resources/kicker.ico");
	trayIcon->setIcon(icon);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->show();

}// END initializeUIComponents

// update the member variables if update button is clicked
void Client_IOB::updateMember()
{
	qDebug() << "Starting update member variables";
	mLocation = locationEdit->text();
	mPhone = phoneEdit->text();
	mNotes = notesEdit->text();
	sendUpdate();
} // END updateMember

// update the status semafore
void Client_IOB::updateStatus(int newStatus)
{
	mStatus = newStatus;
	// set the semafore
	QIcon* iconBlack = new QIcon("Resources/black.png");
	buttonRed->setIcon(*iconBlack);
	buttonYellow->setIcon(*iconBlack);
	buttonGreen->setIcon(*iconBlack);
	
	QIcon* icon = 0;
	switch(mStatus)
	{
	case STATUS::ABSENT:
		icon = new QIcon("Resources/red.png");
		buttonRed->setIcon(*icon);
		break;
	case STATUS::BUSY:
		icon = new QIcon("Resources/yellow.png");
		buttonYellow->setIcon(*icon);
		break;
	case STATUS::AVAILABE:
		icon = new QIcon("Resources/green.png");
		buttonGreen->setIcon(*icon);
	}

	// clean up pointers
	delete icon;
	delete iconBlack;
			
}// END updateStatus

// create action for the tray icon menu
void Client_IOB::createMenuTrayActions()
{
	minimizeAction = new QAction(tr("&Minimize"), this);
	connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

	restoreAction = new QAction(tr("&Restore"), this);
	connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

	quitAction = new QAction(tr("&Quit"), this);
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

}// END createMenuTrayActions

// write the user data into a xml document
void Client_IOB::writeXMLDocument()
{
	// open xml file
	QFile file(mXMLFileName);
	if (!file.open(QFile::WriteOnly))
	{
		// error message
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Unable to write XML file!!");
		messageBox.setFixedSize(500, 200);
		return;
	}

	// write all the status information in the xml document
	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.writeStartElement("client");
	writer.writeAttribute("id", mID.toString());
	writer.writeTextElement("name", mName);
	writer.writeTextElement("status", QString::number(mStatus));
	writer.writeTextElement("location", mLocation);
	writer.writeTextElement("phone", mPhone);
	writer.writeTextElement("notes", mNotes);
	writer.writeEndElement();

	qDebug() << "Wrote XML file:" << mXMLFileName;
}// END writeXMLDocument

// open connection to server
void Client_IOB::contactServer()
{
	mServerAddress = QHostAddress::LocalHost;
	mServerPort = 9000;
	mUrl = QUrl(QString("ws://%1:%2").arg(mServerAddress.toString()).arg(mServerPort));
	qDebug() << mUrl;
	connect(&mWebSocket, &QWebSocket::connected, this, &Client_IOB::onConnected);
	connect(&mWebSocket, &QWebSocket::disconnected, this, &Client_IOB::closed);
	
	try
	{
		mWebSocket.open(QUrl(mUrl));
	}
	catch(QException err)
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "No server connection!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}
	
}

void Client_IOB::onConnected()
{
	qDebug() << "WebSocket connected";
	connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &Client_IOB::onTextMessageReceived);

	this->registerAtServer();
}

void Client_IOB::onTextMessageReceived(QString telegram)
{
	qDebug() << "Message received:" << telegram;
	// control flow for messages
	QStringList content = telegram.split("#");
	int control = content.at(0).toInt();
	switch (control)
	{
	case MESSAGEID::REFUSAL:
		qDebug() << content.at(1);
	case MESSAGEID::UPDATE:
	{
		if (content.at(1) == mID.toString())
		{
			qDebug() << "Thats me. Nothing to do here";
			// todo nothing, maybe an ack to check against sent information
		}
		else
		{
			// todo: update the client list and table
		}
	}
	default:
		break;
	}
}

// starts registration process
void Client_IOB::registerAtServer()
{
	// create registration byte array
	QString registration(QString::number(MESSAGEID::REGISTRATION));
	registration = buildMessageBody(registration);
	qDebug() << registration;

	if (!mWebSocket.sendTextMessage(registration))
	{
		// todo registration failed
		qDebug() << "Registration could not be carried out!";
	}
	// todo if registration succed
}

// todo
void Client_IOB::closed()
{

}

// closing connection from client side
void Client_IOB::closingConnection()
{
	QString closingTelegram(QString::number(MESSAGEID::CLOSING));
	closingTelegram.append("#").append(this->mID.toString());
	if (!mWebSocket.sendTextMessage(closingTelegram))
	{
		qDebug() << "Registration could not be carried out!";
	}
	// close connection nontheless
	mWebSocket.close();
}

// todo send update to server
void Client_IOB::sendUpdate()
{
	QString update(QString::number(MESSAGEID::UPDATE));
	update = buildMessageBody(update);
	qDebug() << update;
	
	if (!mWebSocket.sendTextMessage(update))
	{
		// todo update failed
		qDebug() << "Update not sent";
	}
	// todo if registration succed
	
}

// message body for registration and updates
QString Client_IOB::buildMessageBody(QString telegram)
{
	telegram.append("#").append(this->mID.toString());
	telegram.append("#").append(this->mName);
	telegram.append("#").append(QString::number(this->mStatus));
	telegram.append("#").append(this->mLocation);
	telegram.append("#").append(this->mPhone);
	telegram.append("#").append(this->mNotes);
	return telegram;
}