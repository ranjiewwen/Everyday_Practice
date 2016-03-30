#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include <QDomElement>
#include <QTreeWidgetItem>
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	bool readFile(const QString &fileName);
private:
	void parseBookindexElement(const QDomElement &element);
	void parseEntryElement(const QDomElement &element, QTreeWidgetItem *parent);
	void parsePageElement(const QDomElement &element, QTreeWidgetItem *parent);
	QTreeWidget *treeWidget;
private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
