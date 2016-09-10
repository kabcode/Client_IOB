#pragma once

#include <QString>
#include <QDomDocument>
#include <stdlib.h>

//*******************//
// CLIENT USER CLASS //
//*******************//
// the client user class contains the information of the user itself.
// It will be load upon start from xml file and store there with quitting the app
// While app use the class will be updated an send over tcp to update the server

class Client_User
{
public:
	Client_User();
	Client_User(QDomDocument);
	~Client_User();
	enum mStatus: unsigned int
	{
		AVAILABLE,
		BUSY,
		ABSENT
	};

	// functions
	int getID() { return mID; };

private:
	//  member variables
	int mID;
	unsigned int mStatus;
	QString mClientName;
	QString mLocation;
	int mPhone;
	QString mNotes;

	// member function
	void setupUser(QDomDocument);
};

