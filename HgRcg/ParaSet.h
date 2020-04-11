#pragma once
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <math.h>

#include "cv.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>

using namespace std;
using namespace cv;

typedef enum gesture_enum
{
	Palm = 0,
	Ok = 1,
	Up = 2,
	Down = 3,
	Check = 4,
	Illegal = 5
}Gesture;
typedef enum result_enum
{
	True = 1,
	False = 0
}Result;
typedef vector<Point> curve;
typedef vector<curve> cluster;

extern Mat CprSeg(Mat src);
extern Mat EdgeDtc(Mat gray);
extern curve ContourExtr(Mat image, Mat& imcontour);
extern Vec4i HullDscr(curve contour, Size ImgSize, Point& Dweb, Mat& imhull, Mat& imdefects);
extern Gesture GesDtm(Vec4i cwdpths, Point Dweb, curve contour);
extern void NameShow(Gesture gesture, string HgName, string& gesture_name, string& result_name);
