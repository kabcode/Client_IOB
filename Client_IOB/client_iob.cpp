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
	connect(mTCPSocket, SIGNAL(readyRead()), this, SLOT(showMessage()));
	this->contactServer(mTCPSocket);

	ui.setupUi(this);
	this->initializeUIComponents();

} // END constructor

Client_IOB::~Client_IOB()
{
	writeXMLDocument();
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
			xmlWriter.writeTextElement(QString("id"), "0");
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
	writer.writeTextElement("ID", QString::number(mID));
	writer.writeTextElement("name", mName);
	writer.writeTextElement("status", QString::number(mStatus));
	writer.writeEndElement();

	qDebug() << "Wrote XML file:" << mXMLFileName;
}// END writeXMLDocument

// fill the member variables with the content of the xml document
void Client_IOB::setStatus(QDomDocument doc)
{
	// get the value of the document nodes
	QDomElement root = doc.firstChildElement("client");
	QDomElement domID = root.firstChildElement("ID");
	mID = domID.text().toInt();
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
	// setup editable lines
	this->idEdit = ui.idEdit;
	this->idEdit->setText(QString::number(mID));
	this->nameEdit = ui.nameEdit;
	this->nameEdit->setText(mName);
	this->statusEdit = ui.statuEdit;
	this->statusEdit->setText(QString::number(mStatus));

	// connect update button and update function
	this->updateButton = ui.updateButton;
	connect(this->updateButton, SIGNAL(clicked()), this, SLOT(updateMember()));

}// END initializeUIComponents

// update the member variables if update button is clicked
void Client_IOB::updateMember()
{
	qDebug() << "Starting update member variables";
} // END updateMember

