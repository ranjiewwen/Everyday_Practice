#ifndef QPIXMAPTEST_H
#define QPIXMAPTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_qpixmaptest.h"

class QpixmapTest : public QMainWindow
{
	Q_OBJECT

public:
	QpixmapTest(QWidget *parent = 0);
	~QpixmapTest();
	void paintEvent(QPaintEvent *);
	QImage image;
private:
	Ui::QpixmapTestClass ui;
};

#endif // QPIXMAPTEST_H
