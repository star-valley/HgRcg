#include <opencv2/opencv.hpp>
using namespace cv;
Mat WhtBln(Mat src)
{
	Mat bln;
	vector<Mat> rgbset;

	//��ͨ������
	split(src, rgbset);
	Mat B = rgbset.at(0);
	Mat G = rgbset.at(1);
	Mat R = rgbset.at(2);

	//���ͨ����ƽ��ֵ
	double avB = mean(B)[0];
	double avG = mean(G)[0];
	double avR = mean(R)[0];

	//�����ͨ����ռ����
	double K = (avB + avG + avR) / 3;
	double Kb = K / avB;
	double Kg = K / avG;
	double Kr = K / avR;

	//���°�ƽ���ĸ�ͨ��BGRֵ
	addWeighted(B, Kb, 0, 0, 0, B);
	addWeighted(G, Kg, 0, 0, 0, G);
	addWeighted(R, Kr, 0, 0, 0, R);

	//��ͨ���ϲ�
	merge(rgbset, bln);

	return bln;
}