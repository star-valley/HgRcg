#include "ParaSet.h"

curve ContourExtr(Mat image, Mat& imcontour)
{
	Mat src_image = image;
	Mat binary_image = src_image;



	/*��̬ѧ����*/
	Mat morph_image;
	int length = 3;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(length, length), Point(-1, -1));
	//�ṹԪ�ش�С��ѡȡҲ����Ҫ
	//�ղ�����������
	morphologyEx(binary_image, morph_image, MORPH_DILATE, kernel, Point(-1, -1), 2);



	/*������ȡ*/
	cluster contours;
	vector<Vec4i> hireachy;
	//hireachy���ڼ�¼��Ӧ���������ָ����Ϣ�����������Ļ�����
	//���о�ûɶ���壩
	findContours(morph_image, contours, hireachy, CV_RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());



	/*����ɸѡ*/
	int tag = 0;//Ŀ����������
	int MaxArea = 0, CurrentArea = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		//ɸѡ��׼�����ֱ����������
		Rect rect = boundingRect(contours[i]);
		CurrentArea = rect.width * rect.height;
		if (MaxArea < CurrentArea)
		{
			tag = i;
			MaxArea = CurrentArea;
		}
	}
	curve contour = contours[tag];//contourΪĿ������



	/*����Ŀ������ͼ��*/
	cluster contour_package;
	contour_package.push_back(contour);
	drawContours(imcontour, contour_package, -1, Scalar(255, 255, 255), 1, 8, vector<Vec4i>());



	return contour;
}
