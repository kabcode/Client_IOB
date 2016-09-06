#ifndef CLIENT_IOB_H
#define CLIENT_IOB_H

#include <QtWidgets/QMainWindow>
#include "ui_client_iob.h"

class Client_IOB : public QMainWindow
{
	Q_OBJECT

public:
	Client_IOB(QWidget *parent = 0);
	~Client_IOB();

private:
	Ui::Client_IOBClass ui;
};

#endif // CLIENT_IOB_H
