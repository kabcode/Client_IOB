#include "Client_User.h"

// default constructor
Client_User::Client_User()
{
}// END default constructor

// own constructor with xml document
Client_User::Client_User(QDomDocument doc)
{
	// use the document to setup up the member variables
	setupUser(doc);

}// END own constructor

// destructor
Client_User::~Client_User()
{
}// END destructor

// setupUser (constructor method)
void Client_User::setupUser(QDomDocument doc)
{
	// get the value of the document nodes
	QDomElement root = doc.firstChildElement("client");
	QDomElement domID = root.firstChildElement("ID");
	mID = domID.text().toInt();
	QDomElement domStatus = root.firstChildElement("status");
	mStatus = domStatus.text().toInt();
	QDomElement domName = root.firstChildElement("clientName");
	mClientName = domName.text();
	QDomElement domLocation = root.firstChildElement("clientLocation");
	mLocation = domLocation.text();
	QDomElement domPhone = root.firstChildElement("clientPhone");
	mPhone = domPhone.text().toInt();
	QDomElement domNotes = root.firstChildElement("clientNotes");
	mNotes = domNotes.text();
}// END setupUser
