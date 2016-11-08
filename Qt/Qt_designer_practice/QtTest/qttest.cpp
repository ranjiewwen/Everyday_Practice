#include "qttest.h"
#include<QPushButton>
QtTest::QtTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.btn, &QPushButton::clicked, [this](){close(); });
}

QtTest::~QtTest()
{

}
