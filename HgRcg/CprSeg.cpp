#include "ParaSet.h"

extern Mat WhtBln(Mat src);
extern IplImage* RgbSeg(IplImage* src);
extern IplImage* ElpsSeg(IplImage* src);

//平平淡淡才是真.jpg
Mat CprSeg(Mat src)
{
	/*白平衡*/
	Mat wtbln = WhtBln(src);
	IplImage* wtbln_ipl = (IplImage*)&IplImage(wtbln);

	/*用经光照变换的YCbCr域的椭圆模型进行肤色分割*/
	IplImage* bnr_elps = ElpsSeg(wtbln_ipl);
	Mat bnr_elps_mat = cvarrToMat(bnr_elps);

	/*用RGB域的矩形模型进行肤色分割*/
	IplImage* bnr_rgb = RgbSeg(wtbln_ipl);
	Mat bnr_rgb_mat = cvarrToMat(bnr_rgb);

	/*合并两种方法分割后的图像*/
	Mat bnr_cpr = bnr_elps_mat | bnr_rgb_mat;

	return bnr_cpr;
}