#ifndef QTTEST_H
#define QTTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qttest.h"

class QtTest : public QMainWindow
{
	Q_OBJECT

public:
	QtTest(QWidget *parent = 0);
	~QtTest();
	//QPushBtoon *btn;
private:
	Ui::QtTestClass ui;
};

#endif // QTTEST_H
