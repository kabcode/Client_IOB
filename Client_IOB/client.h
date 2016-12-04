#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QUuid>

class Client : public QObject
{
	Q_OBJECT

public:
	Client(QUuid);
	~Client();
	QString getUuid();
	void changeName(QString);
	void changeStatus(int);
	void changeLocation(QString);
	void changePhone(QString);
	void changeNotes(QString);

private:
	QUuid uuid = QUuid::QUuid();
	QString name;
	int status;
	QString location;
	QString phone;
	QString notes;
};

#endif // CLIENT_H
