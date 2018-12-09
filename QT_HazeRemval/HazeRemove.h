#pragma once
#include<opencv2\opencv.hpp>
#include<iostream>
#include<string>
using namespace cv;
class HazeRemove
{
private:
	int patchRadius;//滤波核大小（半径）
	int globalAtmosphericLight[3];
	float w0;//保证图像中原处景物保留景深而设的参数来保留小部分的雾
	float T0;//不让t的值太小

	void getPatchPosAndSize(Rect &rect, int rows, int cols, int x, int y);
public:
	Mat srcImg;
	Mat tmpSrcImg;
	Mat darkChannelImg;
	Mat transmissionMap;
	Mat guidedfilterTransmissionMap;
	Mat estimatedTransmissionMap;
	//Mat hazeRemoveImg;
	HazeRemove(Mat img,int radius,float coffecient,float t0);
	HazeRemove();
	~HazeRemove();
	void getDarkChannelPrior();
	void getTransmissionMap(bool isUseAverage=true);
	void getEstimatedTransmissionMap(bool isUseAverage=true);
	void getGlobalAtmosphericLight(bool isUseAverage);
	void testImg(std::string input, std::string output);
	Mat getHazeRemoveImg(Mat transmissionMat);
	Mat guidedFilter(cv::Mat I, cv::Mat p, int r, double eps);
	
};


typedef struct{
	int posX;
	int posY;
	int val;
}Pixel;
