#include "ParaSet.h"

curve ContourExtr(Mat image, Mat& imcontour)
{
	Mat src_image = image;
	Mat binary_image = src_image;



	/*形态学操作*/
	Mat morph_image;
	int length = 3;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(length, length), Point(-1, -1));
	//结构元素大小的选取也很重要
	//闭操作不如膨胀
	morphologyEx(binary_image, morph_image, MORPH_DILATE, kernel, Point(-1, -1), 2);



	/*轮廓提取*/
	cluster contours;
	vector<Vec4i> hireachy;
	//hireachy用于记录对应序号轮廓的指引信息，是轮廓集的户政科
	//（感觉没啥意义）
	findContours(morph_image, contours, hireachy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());



	/*轮廓筛选*/
	int tag = 0;//目标轮廓索引
	int MaxArea = 0, CurrentArea = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		//筛选标准是外接直矩形面积最大
		Rect rect = boundingRect(contours[i]);
		CurrentArea = rect.width * rect.height;
		if (MaxArea < CurrentArea)
		{
			tag = i;
			MaxArea = CurrentArea;
		}
	}
	curve contour = contours[tag];//contour为目标轮廓



	/*绘制目标轮廓图像*/
	cluster contour_package;
	contour_package.push_back(contour);
	drawContours(imcontour, contour_package, -1, Scalar(255, 255, 255), 1, 8, vector<Vec4i>());



	return contour;
}
