#include "ParaSet.h"

Mat EdgeDtc(Mat gray)
{
    Mat result;

	//����Ϊ����ͼ���ʽת����ʽ
	//IplImage *ipl = (IplImage *)&IplImage(mat);
	//Mat mat = cvarrToMat(ipl);
    
    Canny(gray, result, 20, 100, 3);
	//canny�㷨������grayΪ����ͼ��resultΪ���ͼ��20Ϊ����ֵ��100Ϊ����ֵ��3Ϊsobel���ӳߴ�

	return result;
}
