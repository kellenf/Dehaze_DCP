#include "QT_HazeRemval.h"
#include <QtWidgets/QApplication>
#include <QFileDialog>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QT_HazeRemval w;
	w.show();
	return a.exec();
}
