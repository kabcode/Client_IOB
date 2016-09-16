

#include "client_iob.h"
// debug library
#include <QDebug>


Client_IOB::Client_IOB(QWidget *parent)
	: QMainWindow(parent),
	mTCPSocket(new QTcpSocket(this)),
	mNetworkSession(Q_NULLPTR)
{
	// start client

	// load xml document with last status
	mStatusXML = this->loadXMLDocument(mXMLFileName);
	
	// set status based on xml document
	this->setStatus(mStatusXML);
	
	// contact server
	//connect(mTCPSocket, SIGNAL(readyRead()), this, SLOT(showMessage()));
	//this->contactServer(mTCPSocket);

	// set UI
	ui.setupUi(this);
	this->initializeUIComponents();

} // END constructor

Client_IOB::~Client_IOB()
{
	writeXMLDocument();
	delete signalMapper;
	delete mTCPSocket;
} // END destructor

  // load the XML document
QDomDocument Client_IOB::loadXMLDocument(QString fileName)
{
	QDomDocument clientXML(fileName);

	// check if client list exist
	QFileInfo checkFile(fileName);
	if (!checkFile.exists() && !checkFile.isFile())
	{
		// create a new xml document
		QFile file(fileName);
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

	// load the xml file as QDomDocument
	QFile xmlFile(fileName);
	// if the file cant be read
	if (!xmlFile.open(QIODevice::ReadOnly))
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Unable to read XML file!!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}
	// content is not correct
	if (!clientXML.setContent(&xmlFile))
	{
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "File contains wrong content!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}

	// return QDomDocument
	return clientXML;
} // END loadXMLDocument

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
	writer.writeTextElement("name",     mName);
	writer.writeTextElement("status",   QString::number(mStatus));
	writer.writeTextElement("location", mLocation);
	writer.writeTextElement("phone",    mPhone);
	writer.writeTextElement("notes",    mNotes);
	writer.writeEndElement();

	qDebug() << "Wrote XML file:" << mXMLFileName;
}// END writeXMLDocument

// fill the member variables with the content of the xml document
void Client_IOB::setStatus(QDomDocument doc)
{
	// get the value of the document nodes
	QDomElement root = doc.firstChildElement("client");
	mID = root.attribute("id").toInt();
	qDebug() << mID;
	// load the app with STATUS::AVAILABLE
	QDomElement domStatus = root.firstChildElement("status");
	/* mStatus = domStatus.text().toInt(); */
	mStatus = STATUS::AVAILABE;
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
		// if use doesnt provide a name
		else
		{
			QMessageBox messageBox;
			messageBox.critical(0, "Error", "No name provided!");
			messageBox.setFixedSize(500, 200);
			QApplication::exit(EXIT_FAILURE);
		}	
	}
	else{ mName = domName.text();}
	qDebug() << mName;
	QDomElement domLocation = root.firstChildElement("location");
	mLocation = domLocation.text();
	QDomElement domPhone = root.firstChildElement("phone");
	mPhone = domPhone.text();
	QDomElement domNotes = root.firstChildElement("notes");
	mNotes = domNotes.text();	
}// END setStatus

// contact the server to establish a connection
void Client_IOB::contactServer(QTcpSocket* socket)
{
	QString temp;
	socket->connectToHost(QHostAddress::LocalHost, 9000);

	if (socket->waitForConnected(-1))
		qDebug() << "connected";
	else {
		qDebug() << "cannot connect";
		return;
	}
}// END contactServer

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
	trayIcon = new QSystemTrayIcon(this);
	QIcon icon = QIcon("Resources/kicker.ico");
	trayIcon->setIcon(icon);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->show();
	//connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

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
	//qDebug() << "New Status: " << mStatus;
	// set the semafore
	QIcon* iconBlack = new QIcon("Resources/black.png");
	buttonRed->setIcon(*iconBlack);
	buttonYellow->setIcon(*iconBlack);
	buttonGreen->setIcon(*iconBlack);
	delete iconBlack;
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
	delete icon;
			
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