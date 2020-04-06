#include "ParaSet.h"

int main()
{
	char HgName[8] = { 0 };
	char index[8] = { 0 };
	printf("Please input the HgName:\n");
	gets_s(HgName, 8);
	printf("Please input the index:\n");
	gets_s(index, 8);

	char folder[] = "D:\\photos_expr\\HGnv\\";
	char file[16] = { 0 };
	char sub_bnr[] = "_bnr", sub_edge[] = "_edge", sub_contour[] = "_contour", sub_hull[] = "_hull", sub_defects[] = "_defects";
	char sub_result[] = "_result";
	char extension[] = ".jpg", extension1[] = ".txt";
	char path[128] = { 0 }, path_bnr[128] = { 0 }, path_edge[128] = { 0 }, path_contour[128] = { 0 }, path_hull[128] = { 0 }, path_defects[128] = { 0 };
	char path_result[128] = { 0 };

	sprintf(file, "%s%s", HgName, index);
	sprintf(path, "%s%s%s", folder, file, extension);
	sprintf(path_bnr, "%s%s%s%s", folder, file, sub_bnr, extension);
	sprintf(path_edge, "%s%s%s%s", folder, file, sub_edge, extension);
	sprintf(path_contour, "%s%s%s%s", folder, file, sub_contour, extension);
	sprintf(path_hull, "%s%s%s%s", folder, file, sub_hull, extension);
	sprintf(path_defects, "%s%s%s%s", folder, file, sub_defects, extension);
	sprintf(path_result, "%s%s%s%s", folder, HgName, sub_result, extension1);

	//��ֵ�ָ�(��ֵͼ��)->��Ե���(��ֵͼ��)
	//->������ȡ(�����������)->����ɸѡ(������)
	//->͹������(����͵�)->����ж�(ö�ٳ�Ա)
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

	char gesture_name[16] = { 0 };
	char result_name[8] = { 0 };
	NameShow(gesture, HgName, gesture_name, result_name);

	//�洢���������
	imwrite(path_bnr, bnr);

	imwrite(path_edge, edge);

	imwrite(path_contour, imcontour);

	imwrite(path_hull, imhull);
	imwrite(path_defects, imdefects);

	FILE* fp = fopen(path_result, "a");
	char note[10] = { 0 };
	sprintf(note, "%s%s", file, "��");
	fprintf(fp, note);
	fprintf(fp, "%s\t", result_name);
	fprintf(fp, "%s", gesture_name);
	fprintf(fp, "\n");
	fclose(fp);

	printf("The gesture is:\n");
	printf("%s\n", gesture_name);
	printf("The result is:\n");
	printf("%s\n", result_name);

	return 0;
}