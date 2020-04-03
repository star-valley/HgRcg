#include "ParaSet.h"

extern Mat WhtBln(Mat src);
extern IplImage* RgbSeg(IplImage* src);
extern IplImage* ElpsSeg(IplImage* src);

//ƽƽ����������.jpg
Mat CprSeg(Mat src)
{
	/*��ƽ��*/
	Mat wtbln = WhtBln(src);
	IplImage* wtbln_ipl = (IplImage*)&IplImage(wtbln);

	/*�þ����ձ任��YCbCr�����Բģ�ͽ��з�ɫ�ָ�*/
	IplImage* bnr_elps = ElpsSeg(wtbln_ipl);
	Mat bnr_elps_mat = cvarrToMat(bnr_elps);

	/*��RGB��ľ���ģ�ͽ��з�ɫ�ָ�*/
	IplImage* bnr_rgb = RgbSeg(wtbln_ipl);
	Mat bnr_rgb_mat = cvarrToMat(bnr_rgb);

	/*�ϲ����ַ����ָ���ͼ��*/
	Mat bnr_cpr = bnr_elps_mat | bnr_rgb_mat;

	return bnr_cpr;
}