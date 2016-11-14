#include "client_iob.h"

//******************//
//   Client Class   //
//******************//

// constructor
Client_IOB::Client_IOB(QWidget *parent)
	: QMainWindow(parent),
	mStatusXML("status"),
	mTcpSocket(new QTcpSocket(this))
{
	// load xml document with last status
	this->loadXMLDocument();
		
	// set status based on xml document
	this->setStatus();
		
	// contact server
	mServerAddress = QHostAddress::LocalHost;
	mServerPort = 9000;
	mUrl = QUrl(QString("ws://%1:%2").arg(mServerAddress.toString()).arg(mServerPort));
	qDebug() << mUrl;
	connect(&mWebSocket, &QWebSocket::connected, this, &Client_IOB::onConnected);
	connect(&mWebSocket, &QWebSocket::disconnected, this, &Client_IOB::closed);
	mWebSocket.open(QUrl(mUrl));
	/*
	
	this->contactServer();
	*/
	// set UI
	ui.setupUi(this);
	this->initializeUIComponents();
	
} // END constructor

// destructor
Client_IOB::~Client_IOB()
{
	
	writeXMLDocument();
	delete trayIconMenu;
	delete signalMapper;
	delete mTcpSocket;
	
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
			xmlWriter.writeAttribute(QString("id"), "0");
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
	mID = root.attribute("id").toInt();
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
		// if user doesnt provide a name
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

// contact the server to establish a connection
/*
void Client_IOB::contactServer()
{
	connect(mTcpSocket, &QTcpSocket::connected,    this, &Client_IOB::connected);
	connect(mTcpSocket, &QTcpSocket::disconnected, this, &Client_IOB::disconnected);
	connect(mTcpSocket, &QTcpSocket::bytesWritten, this, &Client_IOB::bytesWritten);
	connect(mTcpSocket, &QTcpSocket::readyRead,    this, &Client_IOB::readyRead);

	qDebug() << "Connecting to: " << mServerAddress << " Port: " << mServerPort;
	mTcpSocket->connectToHost(mServerAddress, mServerPort);

	if (!mTcpSocket->waitForConnected(3000))
	{
		qDebug() << "Error " << mTcpSocket->errorString();
	}

}// END contactServer

// SLOT: when activated send the own id to the server to start update cycle
void Client_IOB::connected()
{
	qDebug() << "Connected!";
	// send ID to server
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_5_7);

	// first send ID to update the servers list
	out << mID;
	mTcpSocket->write(block);
	mTcpSocket->flush();
	qDebug() << "ID sent";
}
*/
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

/*
void Client_IOB::disconnected()
{
	qDebug() << "Disconnected!";
	mTcpSocket->close();
}
void Client_IOB::bytesWritten(qint64 bytes)
{
	qDebug() << "Wrote" << bytes << "Bytes.";
}
void Client_IOB::readyRead()
{
	qDebug() << "Reading...";
	QDataStream clientReadStream(mTcpSocket);
	QString message;

	clientReadStream >> message;
	qDebug() << message;
}
*/
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
	writer.writeAttribute("id", QString::number(mID));
	writer.writeTextElement("name", mName);
	writer.writeTextElement("status", QString::number(mStatus));
	writer.writeTextElement("location", mLocation);
	writer.writeTextElement("phone", mPhone);
	writer.writeTextElement("notes", mNotes);
	writer.writeEndElement();

	qDebug() << "Wrote XML file:" << mXMLFileName;
}// END writeXMLDocument

void Client_IOB::onConnected()
{
	qDebug() << "WebSocket connected";
	connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &Client_IOB::onTextMessageReceived);
	mWebSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void Client_IOB::onTextMessageReceived(QString message)
{
	qDebug() << "Message received:" << message;
	mWebSocket.close();
}
