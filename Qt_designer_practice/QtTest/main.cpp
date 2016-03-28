#include "qttest.h"
#include <QtWidgets/QApplication>
#include<qtranslator.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    QTranslator *translator=new QTranslator;
    translator->load("C:/Users/CMOS/Desktop/Everyday_Practice/Qt_designer_practice/QtTest/QtTest.qm");
    a.installTranslator(translator);
	QtTest w;
	w.show();
	return a.exec();
}
