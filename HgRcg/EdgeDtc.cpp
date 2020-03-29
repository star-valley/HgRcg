#include "ParaSet.h"

Mat EdgeDtc(Mat gray)
{
    Mat result;

	//以下为两种图像格式转换方式
	//IplImage *ipl = (IplImage *)&IplImage(mat);
	//Mat mat = cvarrToMat(ipl);
    
    Canny(gray, result, 20, 100, 3);
	//canny算法函数，gray为输入图像，result为输出图像，20为低阈值，100为高阈值，3为sobel算子尺寸

	return result;
}
