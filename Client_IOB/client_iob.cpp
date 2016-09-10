#include "client_iob.h"



Client_IOB::Client_IOB(QWidget *parent)
	: QMainWindow(parent)
{
	// start client

	// load xml document with last status
	mStatusXML = loadXMLDocument(mXMLFileName);

	// set user object
	mUser = Client_User(mStatusXML);

	// 

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
			// create the base structure for xml file
			QXmlStreamWriter xmlWriter(&file);
			xmlWriter.setAutoFormatting(true);
			xmlWriter.writeStartDocument();
			xmlWriter.writeStartElement("client");
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
	if (!xmlFile.open(QIODevice::ReadOnly))
	{
		xmlFile.close();
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "Unable to read XML file!!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}
	if (!clientXML.setContent(&xmlFile))
	{
		xmlFile.close();
		QMessageBox messageBox;
		messageBox.critical(0, "Error", "File contains wrong contaent!");
		messageBox.setFixedSize(500, 200);
		QApplication::exit(EXIT_FAILURE);
	}

	// return QDomDocument
	return clientXML;
} // END loadXMLDocument
