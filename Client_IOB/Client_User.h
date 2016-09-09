#pragma once

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
	~Client_User();
};

