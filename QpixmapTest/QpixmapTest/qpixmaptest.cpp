#include "qpixmaptest.h"
class QImage;
class QPainter;
#include <QPainter>
QpixmapTest::QpixmapTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	image.load("C:\\Users\\ranji\\Desktop\\IMG_20130820_161722.jpg");
	
}
void QpixmapTest::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QPixmap pic = QPixmap::fromImage(image.scaled(size(),Qt::IgnoreAspectRatio));
	painter.drawPixmap(0, 0, pic);
	//painter.drawImage(0, 0, image);
}
QpixmapTest::~QpixmapTest()
{

}
