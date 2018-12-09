#include "HazeRemove.h"
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int compareMyType(const void * a, const void * b)
{
	if (((Pixel*)a)->val <  ((Pixel*)b)->val) return 1;
	if (((Pixel*)a)->val == ((Pixel*)b)->val) return 0;
	if (((Pixel*)a)->val >((Pixel*)b)->val) return -1;
}


HazeRemove::HazeRemove(Mat img, int radius, float coffecient,float t0) :w0(coffecient),T0(t0)
{
	srcImg = img;
	tmpSrcImg = srcImg.clone();
	resize(srcImg, srcImg, Size(), 0.5, 0.5);
	//ʹ��Mat.create(��������)��������һ������,
	darkChannelImg.create(srcImg.rows, srcImg.cols, CV_8UC1);
	transmissionMap.create(srcImg.rows, srcImg.cols, CV_32F);
	estimatedTransmissionMap.create(srcImg.rows, srcImg.cols, CV_32F);
	patchRadius = radius;
	for (int i = 0; i < 3; i++)
		globalAtmosphericLight[i] = 0;
	
}
HazeRemove::HazeRemove() {}

HazeRemove::~HazeRemove()
{
}


/*
*rect:�õ���patch
*rows:ͼ��ĳ���
*cols:ͼ��Ŀ��
*x:patch���Ͻ����ڵ�x����
*y:patch���Ͻ����ڵ�y����
*/
void HazeRemove::getPatchPosAndSize(Rect &rect,int rows,int cols,int x,int y)
{
	int i = y;
	int j = x;
	if (j - patchRadius < 0)
	{
		rect.x = 0;
		rect.width = j + patchRadius;
		if (i - patchRadius < 0)
		{
			rect.y = 0;
			rect.height = i + patchRadius;
		}
		else{
			rect.y = i - patchRadius;
			rect.height = i + patchRadius >= rows ? patchRadius + rows - i : 2 * patchRadius + 1;
		}
	}
	else if (i - patchRadius <= 0)
	{
		rect.y = 0;
		rect.height = i + patchRadius;
		rect.x = j - patchRadius;
		rect.width = j + patchRadius >= cols ? patchRadius + cols - j : 2 * patchRadius + 1;
	}
	else if (i + patchRadius >= rows)
	{
		rect.y = i - patchRadius;
		rect.height = patchRadius + rows - i;
		rect.x = j - patchRadius;
		rect.width = j + patchRadius >= cols ? patchRadius + cols - j : 2 * patchRadius + 1;
	}
	else if (j + patchRadius >= cols)
	{
		rect.x = j - patchRadius;
		rect.width = j + patchRadius >= cols ? patchRadius + cols - j : 2 * patchRadius + 1;
		rect.y = i - patchRadius;
		rect.height = 2 * patchRadius + 1;
	}
	else{
		rect.x = j - patchRadius;
		rect.y = i - patchRadius;
		rect.height = 2 * patchRadius + 1;
		rect.width = 2 * patchRadius + 1;
	}
}

void HazeRemove::getDarkChannelPrior()
{
	int rows = srcImg.rows;
	int cols = srcImg.cols;
	int nchannels = srcImg.channels();
	Mat tmpMat=darkChannelImg.clone();

	//if the image is continus, transform it into 1-dimension to make the operation faster
	if (srcImg.isContinuous())
	{
		cols = cols*rows;
		rows = 1;
	}
	for (int i = 0; i < rows; i++)
	{
		uchar* srcData = srcImg.ptr<uchar>(i);//ָ���i�е�һ��Ԫ�ص�ָ��
		uchar* tmpData = tmpMat.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			*tmpData = *srcData;
			//get the mimum value of R,G,B in each pixel
			for (int p = 1; p < nchannels; p++)
			{
				if (*tmpData>*(srcData + p))
					*tmpData = *(srcData + p);
			}
			tmpData++;
			srcData = srcData + nchannels;
		}
	}
	//minmum filter in the patch
	cols = tmpMat.cols;
	rows = tmpMat.rows;
	//if patchRaius is small,don' use fast minfilter method.
	if (patchRadius > 9)
	{
		for (int i = 0; i < rows; i+=patchRadius)
		{
			for (int j = 0; j < cols; j+=patchRadius)
			{
				//set the patch size and position
				Rect rect;
				getPatchPosAndSize(rect, rows, cols, j, i);

				//find the minimum in patch
				Mat patchImg = tmpMat(rect);
				double minimum = 0;
				minMaxLoc(patchImg, &minimum);

				//set the minimum to each pixel in the patch 
				for (int patch_y = rect.y; patch_y < rect.y + rect.height; patch_y++)
				{
					//��ס���Mat�������͵ķ��ʷ���
					uchar* darkPriorData = darkChannelImg.ptr<uchar>(patch_y);
					for (int patch_x = rect.x; patch_x < rect.x + rect.width; patch_x++)
						*(darkPriorData + patch_x) = (int)minimum;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < rows; i+=patchRadius)
		{
			for (int j = 0; j < cols; j+=patchRadius)
			{
				double minimum = 300;
				for (int x = i; x < i+patchRadius &&x<rows; x++)
				{
					uchar *darkPriorData = tmpMat.ptr<uchar>(x);
					for (int y = j; y < j + patchRadius &&y<cols; y++)
						if (minimum > *(darkPriorData + y))
							minimum = *(darkPriorData + y);
				}
				for (int x = i; x < i + patchRadius&&x<rows; x++)
				{
					uchar *darkPriorData = darkChannelImg.ptr<uchar>(x);
					for (int y = j; y < j + patchRadius&& y<cols; y++)
						*(darkPriorData + y)=(int)minimum;
				}
			}
		}
	}

	
}

void HazeRemove::getTransmissionMap(bool isUseAverage)
{	
	getGlobalAtmosphericLight(isUseAverage);
	const int rows = darkChannelImg.rows;
	const int cols = darkChannelImg.cols;
	const int nChannels = srcImg.channels();
	Mat tmpMat(rows, cols, CV_32F);
	//get the transmission map
	for (int i = 0; i < rows; i++)
	{
		uchar* pdata = srcImg.ptr<uchar>(i);
		//float* transmissinData = transmissionMap.ptr<float>(i);
		float* tmpData = tmpMat.ptr<float>(i);
		for (int j = 0; j < cols; j++)
		{
			float BVal = (float)*(pdata + j*nChannels);
			float GVal = (float)*(pdata + j*nChannels + 1);
			float RVal = (float)*(pdata + j*nChannels + 2);
			float tmp = BVal / globalAtmosphericLight[0] < GVal / globalAtmosphericLight[1] ? (BVal / globalAtmosphericLight[0]) : (GVal / globalAtmosphericLight[1]);
			float minVal = tmp < RVal / globalAtmosphericLight[2] ? tmp : (RVal / globalAtmosphericLight[2]);
			//*transmissinData++ = (1 - w0*minVal <= T0) ? T0 : (1 -w0*minVal);//minVal may be larger than 1
			*tmpData++ = minVal;
		}
	}
	//get the estimated transmission map
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Rect rect;
			getPatchPosAndSize(rect, rows, cols, j, i);

			//find the minimum in patch
			Mat patchImg = tmpMat(rect);
			double minimum = 0;
			minMaxLoc(patchImg, &minimum);

			//set the minimum to each pixel in the patch 
			for (int patch_y = rect.y; patch_y < rect.y + rect.height; patch_y++)
			{
				float* transmissionData = transmissionMap.ptr<float>(patch_y);
				for (int patch_x = rect.x; patch_x < rect.x + rect.width; patch_x++)
					//����͸����t
					*(transmissionData + patch_x) = (1 - w0*minimum <= T0) ? T0 : (1 - w0*minimum);//minVal may be larger than 1;
			}
		}
	}
}
void HazeRemove::getGlobalAtmosphericLight(bool isUseAverage)
//�����������ֵ
{
	const float brightes_ratio = 0.001;
	int rows = darkChannelImg.rows;
	int cols = darkChannelImg.cols;
	int brightestPixelNum = (int)(brightes_ratio*rows*cols);
	int count = 0;
	vector<Pixel> pixelContainer;
	/*
	if (darkChannelImg.isContinuous())
	{
		cols = cols*rows;
		rows = 1;
	}
	*/
	for (int i = 0; i < rows; i++)
	{
		uchar* srcData = darkChannelImg.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			Pixel p;
			p.posX = j;
			p.posY = i;
			p.val = *(srcData + j);
			pixelContainer.push_back(p);
		}
	}
	qsort(&pixelContainer[0], pixelContainer.size(), sizeof(Pixel), compareMyType);
	//get the globalAtmosphericLight in each channel
	float average[3] = { 0, 0, 0 };
	float max[3] = { 0, 0, 0 };
	int nChannels = srcImg.channels();
	for (int c = 0; c < nChannels; c++)
	{
		int sum = 0;
		for (int iter = 0; iter < brightestPixelNum; iter++)
		{
			int x = pixelContainer[iter].posX;
			int y = pixelContainer[iter].posY;
			uchar* fogImgData = srcImg.ptr<uchar>(y);
			//�޸���һ��bug
			if (isUseAverage)
			{
				sum += *(fogImgData + nChannels*x + c);
			}
			else{
				if (max[c] < *(fogImgData + nChannels*x + c))
					max[c] = *(fogImgData + nChannels*x + c);
			}
		}
		if (isUseAverage)
		{
			average[c] = (float)sum / (float)brightestPixelNum;
			globalAtmosphericLight[c] = average[c];
		}
		else
			globalAtmosphericLight[c] = max[c];
	}
}

void HazeRemove::getEstimatedTransmissionMap(bool isUseAverage)
{
	getGlobalAtmosphericLight(isUseAverage);
	const int rows = darkChannelImg.rows;
	const int cols = darkChannelImg.cols;
	int channelsNum = srcImg.channels();
	if (abs(globalAtmosphericLight[0]) < 0.1)
		cout << "sdasdasdasdasdasd";
	//get the transmission map
	for (int i = 0; i < rows; i+=patchRadius)
	{
		uchar* pdata = srcImg.ptr<uchar>(i);
		float* transmissinData = estimatedTransmissionMap.ptr<float>(i);
		for (int j = 0; j < cols; j+=patchRadius)
		{
			float min_val = INT_MAX;
			//compute the min_val in this patch
			for (int x = i; x < rows&&x < i + patchRadius; x++)
			{
				//uchar *color_val = srcImg.ptr<uchar>(x);
				for (int y = j; y < cols&&y < j + patchRadius; y++)
				{
					//color_val += y * channelsNum;
					//this is a bug when visit value of color_val
					int v = srcImg.at<Vec3b>(x,y)[0];
					float ratio = v / (float)globalAtmosphericLight[0];
					if (ratio < min_val)
						min_val = ratio;
					for (int t = 1; t < channelsNum; ++t)
					{
						ratio = srcImg.at<Vec3b>(x, y)[0] / (float)globalAtmosphericLight[t];
						if (ratio < min_val)
							min_val = ratio;
					}
				}
			}
			//comput the transmission
			for (int x = i; x < rows&&x < i + patchRadius; x++)
			{
				float *color_val = estimatedTransmissionMap.ptr<float>(x);
				for (int y = j; y < cols&&y < j + patchRadius; y++)
				{
					*(color_val+y) = (1-w0*min_val)>T0?1-w0*min_val:T0;
				}
			}
		}
		cout << endl;
	} 
}

Mat HazeRemove::getHazeRemoveImg(Mat transmissionMat)
{
	int rows = tmpSrcImg.rows;
	int cols = tmpSrcImg.cols;
	Mat hazeRemoveImg(tmpSrcImg.rows, tmpSrcImg.cols, CV_32FC3);
	const int nchannels = tmpSrcImg.channels();
	resize(transmissionMat, transmissionMat, Size(cols, rows));
	//if the image is continus, transform it into 1-dimension to make the operation faster
	if (tmpSrcImg.isContinuous())
	{
		cols = cols*rows;
		rows = 1;
	}
	for (int i = 0; i < rows; i++)
	{
		uchar* srcData = tmpSrcImg.ptr<uchar>(i);
		float* dstData = hazeRemoveImg.ptr<float>(i);
		float* transData = transmissionMat.ptr<float>(i);//TODO:select the transmissionMap or estimatedTransmissionMap
		for (int j = 0; j < cols; j++)
		{
			float TVal = *(transData + j);
			for (int c = 0; c < nchannels; c++)
			{		
				*(dstData + nchannels*j + c) = (*(srcData + nchannels*j + c) - globalAtmosphericLight[c]) / (TVal*255.0) + globalAtmosphericLight[c]/255.0;
			}
		}	
	}
	return hazeRemoveImg;
}

Mat HazeRemove::guidedFilter(cv::Mat I, cv::Mat p, int r, double eps)
{
	/*
	% GUIDEDFILTER   O(1) time implementation of guided filter.
	%
	%   - guidance image: I (should be a gray-scale/single channel image),use the fog image as the guidance image.
	%   - filtering input image: p (should be a gray-scale/single channel image)
	%   - local window radius: r
	%   - regularization parameter: eps
	*/
	resize(I,I, Size(p.cols, p.rows));
	cv::Mat _I;
	I.convertTo(_I, CV_32FC1);
	I = _I;

	cv::Mat _p;
	p.convertTo(_p, CV_32FC1);
	p = _p;

	//[height, width] = size(I);
	int height = I.rows;
	int width = I.cols;

	//N = boxfilter(ones(height, width), r); % the size of each local patch; N=(2r+1)^2 except for boundary pixels.
	cv::Mat N;
	cv::boxFilter(cv::Mat::ones(height, width, I.type()), N, CV_32FC1, cv::Size(r, r));

	//mean_I = boxfilter(I, r) ./ N;
	cv::Mat mean_I;
	cv::boxFilter(I, mean_I, CV_32FC1, cv::Size(r, r));

	//mean_p = boxfilter(p, r) ./ N;
	cv::Mat mean_p;
	cv::boxFilter(p, mean_p, CV_32FC1, cv::Size(r, r));

	//mean_Ip = boxfilter(I.*p, r) ./ N;
	cv::Mat mean_Ip;
	cv::boxFilter(I.mul(p), mean_Ip, CV_32FC1, cv::Size(r, r));

	//cov_Ip = mean_Ip - mean_I .* mean_p; % this is the covariance of (I, p) in each local patch.
	cv::Mat cov_Ip = mean_Ip - mean_I.mul(mean_p);

	//mean_II = boxfilter(I.*I, r) ./ N;
	cv::Mat mean_II;
	cv::boxFilter(I.mul(I), mean_II, CV_32FC1, cv::Size(r, r));

	//var_I = mean_II - mean_I .* mean_I;
	cv::Mat var_I = mean_II - mean_I.mul(mean_I);

	//a = cov_Ip ./ (var_I + eps); % Eqn. (5) in the paper;	
	cv::Mat a = cov_Ip / (var_I + eps);

	//b = mean_p - a .* mean_I; % Eqn. (6) in the paper;
	cv::Mat b = mean_p - a.mul(mean_I);

	//mean_a = boxfilter(a, r) ./ N;
	cv::Mat mean_a;
	cv::boxFilter(a, mean_a, CV_32FC1, cv::Size(r, r));
	mean_a = mean_a / N;

	//mean_b = boxfilter(b, r) ./ N;
	cv::Mat mean_b;
	cv::boxFilter(b, mean_b, CV_32FC1, cv::Size(r, r));
	mean_b = mean_b / N;

	//q = mean_a .* I + mean_b; % Eqn. (8) in the paper;
	guidedfilterTransmissionMap = mean_a.mul(I) + mean_b;
	//q.copyTo();
	return guidedfilterTransmissionMap;
}