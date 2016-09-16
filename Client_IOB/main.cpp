// memory leak detection
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "client_iob.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
#ifndef NDEBUG

	// get current dbg flag (report it)
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

	// logically OR leak check bit
	flag |= _CRTDBG_LEAK_CHECK_DF;

	// set the flags again
	_CrtSetDbgFlag(flag);

#endif
	// put this right after the flag settings from above
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	QApplication a(argc, argv);
	Client_IOB w;
	w.show();
	// dump memory
	_CrtDumpMemoryLeaks();
	return a.exec();
}
