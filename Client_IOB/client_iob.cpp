#include "client_iob.h"



Client_IOB::Client_IOB(QWidget *parent)
	: QMainWindow(parent)
{
	// start client

	// load xml document with last status
	mStatusXML = loadXMLDocument(mXMLFileName);

	// set status based on xml document
	setStatus(mStatusXML);

	ui.setupUi(this);
} // END constructor

Client_IOB::~Client_IOB()
{
	
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
			xmlWriter.writeTextElement(QString("status"), QString(Client_IOB::STATUS::ABSENT));
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

// fill the member variables with the content of the xml document
void Client_IOB::setStatus(QDomDocument doc)
{
	// get the value of the document nodes
	QDomElement root = doc.firstChildElement("client");
	QDomElement domID = root.firstChildElement("ID");
	mID = domID.text().toInt();
	QDomElement domStatus = root.firstChildElement("status");
	mStatus = domStatus.text().toInt();
	QDomElement domName = root.firstChildElement("name");
	mName = domName.text();

	// if the name tag is empty ask for user name
	if (mName.isEmpty())
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
	
}// END setStatus
