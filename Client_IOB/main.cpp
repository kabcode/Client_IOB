#include "client_iob.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Client_IOB w;
	w.show();
	return a.exec();
}
