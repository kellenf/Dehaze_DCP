#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QT_HazeRemval.h"

class QT_HazeRemval : public QMainWindow
{
	Q_OBJECT

public:
	bool f = true;
	QT_HazeRemval(QWidget *parent = Q_NULLPTR);

private:
	Ui::QT_HazeRemvalClass ui;
	QString open_files;
	QString save_files;
	bool process_one = false;
private slots:
	void Open();
	void Save();
	void Start();
	void ChangeMode();

};
