#include "mainwindow.h"
#include <QtWidgets/QApplication>

//1. 项目->属性->c/c++->常规->附加包含目录->在弹出的对话框中，点那个文件夹形状的按钮添加新行，输入$(QTDIR)\include\QtNetwork

//2. 项目->属性->连接器->输入->附加依赖项，添加 Qt5Networkd.lib（debug模式）或者 Qt5Network.lib（release模式）
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.readFile("books.xml");
	w.show();
	return a.exec();
}
