#include "QT_HazeRemval.h"
#include <QFileDialog>
#include<iostream>
#include "HazeRemove.h"
using namespace std;
using namespace cv;
QT_HazeRemval::QT_HazeRemval(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.open_file, SIGNAL(clicked()), this, SLOT(Open()));
	connect(ui.save_file, SIGNAL(clicked()), this, SLOT(Save()));
	connect(ui.start, SIGNAL(clicked()), this, SLOT(Start()));
	connect(ui.many, SIGNAL(clicked()), this, SLOT(ChangeMode()));
	connect(ui.one, SIGNAL(clicked()), this, SLOT(ChangeMode()));
}
void QT_HazeRemval::ChangeMode()
{
	process_one = !process_one;
	if (process_one)
	{
		ui.open_file->setText(QStringLiteral("打开图片"));
		ui.one->setChecked(true);
		ui.many->setChecked(false);
	}
	else
	{
		ui.open_file->setText(QStringLiteral("打开文件夹"));
		ui.one->setChecked(false);
		ui.many->setChecked(true);
	}
}
void QT_HazeRemval::Open()
{
	if (!process_one)
	{
		open_files = QFileDialog::getExistingDirectory(NULL, "C://Users//kellen//Downloads");
		ui.open_path->setText(open_files);
	}
	else
	{
		open_files = QFileDialog::getOpenFileName(NULL, "C://Users//kellen//Downloads");
		ui.open_path->setText(open_files);
	}
}
void QT_HazeRemval::Save()
{
	save_files = QFileDialog::getExistingDirectory(NULL, "C://Users//kellen//Downloads");
	ui.save_path->setText(save_files);
}
void QT_HazeRemval::Start()
{

	float w0 = (float)ui.W0->value()/ui.W0->maximum();
	QString tmp = ui.patch_r->text();
	int patchRadio = tmp.toUInt();
	tmp = ui.r->text();
	int r = tmp.toUInt();
	float T0 = (ui.T0->value())*1.0 / ui.T0->maximum();
	int eps = 0.001;
	int i = 0;
	string src_path = open_files.toStdString();
	string save_path = save_files.toStdString();
	if (!process_one)
	{
		src_path += "/*.jpg";
		vector<cv::String>pathes;
		cv::glob((cv::String)src_path, pathes, false);
		int amount = pathes.size();
		for (cv::String path : pathes)
		{
			i++;
			int pos = path.find_last_of("\\");
			string img_name = path.substr(pos + 1);
			Mat img = imread(path);
			QString Qpath = QString::fromStdString(path);
			QPixmap img0(Qpath);
			ui.image0->setPixmap(img0);
			Mat gray;
			cvtColor(img, gray, CV_BGR2GRAY);
			HazeRemove hazeRomove(img, patchRadio, w0, T0);
			hazeRomove.getDarkChannelPrior();
			hazeRomove.getEstimatedTransmissionMap(true);
			hazeRomove.guidedFilter(gray, hazeRomove.estimatedTransmissionMap, r, eps);
			Mat filterGuidedHazeRemoveImg = hazeRomove.getHazeRemoveImg(hazeRomove.guidedfilterTransmissionMap);
			string save_ = save_path + "//" + img_name;
			filterGuidedHazeRemoveImg.convertTo(filterGuidedHazeRemoveImg, CV_8UC3, 255);
			//filterGuidedHazeRemoveImg.convertTo(tmp, CV_32FC3);
			imwrite(save_, filterGuidedHazeRemoveImg);
			Qpath = QString::fromStdString(save_);
			QPixmap img1(Qpath);
			ui.image1->setPixmap(img1);
			int value = (int)(100 * i*1.0 / amount);
			ui.progressBar->setValue(value);
			//imwrite(save_, filterGuidedHazeRemoveImg);
		}
	}
	else
	{
		int pos = src_path.find_last_of('/');
		string img_name = src_path.substr(pos + 1);
		Mat img = imread(src_path);
		QString Qpath = QString::fromStdString(src_path);
		QPixmap img0(Qpath);
		ui.image0->setPixmap(img0);
		Mat gray;
		cvtColor(img, gray, CV_BGR2GRAY);
		HazeRemove hazeRomove(img, patchRadio, w0, T0);
		hazeRomove.getDarkChannelPrior();
		hazeRomove.getEstimatedTransmissionMap(true);
		hazeRomove.guidedFilter(gray, hazeRomove.estimatedTransmissionMap, r, eps);
		Mat filterGuidedHazeRemoveImg = hazeRomove.getHazeRemoveImg(hazeRomove.guidedfilterTransmissionMap);
		string save_ = save_path + "//" + img_name;
		filterGuidedHazeRemoveImg.convertTo(filterGuidedHazeRemoveImg, CV_8UC3, 255);
		imwrite(save_, filterGuidedHazeRemoveImg);
		Qpath = QString::fromStdString(save_);
		QPixmap img1(Qpath);
		ui.image1->setPixmap(img1);
	}
}
