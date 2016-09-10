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
	
}// END setupUser
