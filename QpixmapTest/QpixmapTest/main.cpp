#include "qpixmaptest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QpixmapTest w;
	w.show();
	return a.exec();
}
