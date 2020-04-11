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

	//��ֵ�ָ�(��ֵͼ��)->��Ե���(��ֵͼ��)
	//->������ȡ(�����������)->����ɸѡ(������)
	//->͹������(����͵�)->��������ж�(ö�ٳ�Ա)
	Mat src = imread(path, 1);
	if (src.empty())
	{
		printf("�ļ������ڻ����ʧ�ܣ������Լ�飺\n");
		printf("1.�ļ�·���Ƿ���ȷ\n2.imread�����Ƿ�ʹ������\n");
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

	//�洢���������
	imwrite(path_bnr, bnr);

	imwrite(path_edge, edge);

	imwrite(path_contour, imcontour);

	imwrite(path_hull, imhull);
	imwrite(path_defects, imdefects);

	ofstream record;
	record.open(path_result, ios::app);
	record << file << "��\t" << result_name << "\t" << gesture_name << endl;

	cout << "The gesture is:" << endl << gesture_name << endl;
	cout << "The result is:" << endl << result_name << endl;

	return 0;
}
