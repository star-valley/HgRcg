#include "ParaSet.h"

int main()
{
	string HgName, index;
	cout << "Please input the HgName:" << endl;
	cin >> HgName;
	cout << "Please input the index" << endl;
	cin >> index;

	string folder = "D:\\photos_expr\\HGnv\\";
	string file = HgName + index;
	string path = folder + file + ".jpg";
	string path_bnr = folder + file + "_bnr" + ".jpg";
	string path_edge = folder + file + "_edge" + ".jpg";
	string path_contour = folder + file + "_contour" + ".jpg";
	string path_hull = folder + file + "_hull" + ".jpg";
	string path_defects = folder + file + "_defects" + ".jpg";
	string path_result = folder + HgName + "_result" + ".txt";

	//阈值分割(二值图像)->边缘检测(二值图像)
	//->轮廓提取(点数组的数组)->轮廓筛选(点数组)
	//->凸包描述(数组和点)->手势类别判定(枚举成员)
	Mat src = imread(path, 1);
	if (src.empty())
	{
		printf("文件不存在或加载失败！您可以检查：\n");
		printf("1.文件路径是否正确\n2.imread函数是否使用正常\n");
		return -1;
	}

	Mat bnr = CprSeg(src);

	Mat edge = EdgeDtc(bnr);

	Mat imcontour = Mat::zeros(edge.size(), CV_8UC3);
	curve contour = ContourExtr(edge, imcontour);

	Point Dweb;
	Mat imhull = Mat::zeros(edge.size(), CV_8UC3);
	Mat imdefects = Mat::zeros(edge.size(), CV_8UC3);
	Vec4i cwdpths = HullDscr(contour, edge.size(), Dweb, imhull, imdefects);

	Gesture gesture = GesDtm(cwdpths, Dweb, contour);

	string gesture_name;
	string result_name;
	NameShow(gesture, HgName, gesture_name, result_name);

	//存储和输出部分
	imwrite(path_bnr, bnr);

	imwrite(path_edge, edge);

	imwrite(path_contour, imcontour);

	imwrite(path_hull, imhull);
	imwrite(path_defects, imdefects);

	ofstream record;
	record.open(path_result, ios::app);
	record << file << "：\t" << result_name << "\t" << gesture_name << endl;

	cout << "The gesture is:" << endl << gesture_name << endl;
	cout << "The result is:" << endl << result_name << endl;

	return 0;
}
