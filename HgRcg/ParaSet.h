#pragma once
#include <stdio.h>
#include <iostream>

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
	Check = 1,
	Victory = 2,
	Illegal = 3
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
extern Vec4i HullDscr(curve contour, Size ImgSize, Mat& imhull, Mat& imdefects);
extern Gesture HullDtm(Vec4i cwdpths);
extern void NameShow(Gesture gesture, char* HgName, char* gesture_name, char* result_name);
