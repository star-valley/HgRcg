#include <opencv2/opencv.hpp>
using namespace cv;
Mat WhtBln(Mat src)
{
	Mat bln;
	vector<Mat> rgbset;

	//各通道分离
	split(src, rgbset);
	Mat B = rgbset.at(0);
	Mat G = rgbset.at(1);
	Mat R = rgbset.at(2);

	//求各通道的平均值
	double avB = mean(B)[0];
	double avG = mean(G)[0];
	double avR = mean(R)[0];

	//求出个通道所占增益
	double K = (avB + avG + avR) / 3;
	double Kb = K / avB;
	double Kg = K / avG;
	double Kr = K / avR;

	//更新白平衡后的各通道BGR值
	addWeighted(B, Kb, 0, 0, 0, B);
	addWeighted(G, Kg, 0, 0, 0, G);
	addWeighted(R, Kr, 0, 0, 0, R);

	//各通道合并
	merge(rgbset, bln);

	return bln;
}