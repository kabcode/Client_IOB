#include "client.h"

Client::Client(QUuid uuid)
	: uuid(uuid)
{
	
}

Client::~Client()
{

}

QString Client::getUuid() {	return uuid.toString(); }
void Client::changeName(QString name) { this->name = name; }
void Client::changeStatus(int status) { this->status = status; }
void Client::changeLocation(QString location) { this->location = location; }
void Client::changePhone(QString phone) { this->phone = phone; }
void Client::changeNotes(QString notes) { this->notes = notes; }
