#include "ParaSet.h"

int main()
{
	char HgName[8] = { 0 };
	char index[8] = { 0 };
	printf("Please input the HgName:\n");
	gets_s(HgName, 8);
	printf("Please input the index:\n");
	gets_s(index, 8);
	//若图片均为jpg格式，且不更改文件夹，则修改手势类型和序号即可

	char folder[] = "D:\\photos_expr\\HGn\\";

	char file[16] = { 0 };
	char sub_bnr[] = "_bnr", sub_edge[] = "_edge", sub_contour[] = "_contour", sub_FDV[] = "_FDV", sub_hull[] = "_hull", sub_defects[] = "_defects";
	char extension[] = ".jpg", extension1[] = ".txt";
	char path[128] = { 0 }, path_bnr[128] = { 0 }, path_edge[128] = { 0 }, path_contour[128] = { 0 }, path_FDV[128] = { 0 }, path_hull[128] = { 0 }, path_defects[128] = { 0 };

	sprintf(file, "%s%s", HgName, index);
	sprintf(path, "%s%s%s", folder, file, extension);
	sprintf(path_bnr, "%s%s%s%s", folder, file, sub_bnr, extension);
	sprintf(path_edge, "%s%s%s%s", folder, file, sub_edge, extension);
	sprintf(path_contour, "%s%s%s%s", folder, file, sub_contour, extension);
	sprintf(path_FDV, "%s%s%s", folder, HgName, extension1);
	sprintf(path_hull, "%s%s%s%s", folder, file, sub_hull, extension);
	sprintf(path_defects, "%s%s%s%s", folder, file, sub_defects, extension);

	//阈值分割(二值图像)->边缘检测(二值图像)
	//->轮廓提取(点数组的数组)->轮廓筛选(点数组)
	//->归一化傅里叶描述子分析(实数数组)
	IplImage* src=cvLoadImage(path,1);
	int Eff_FDV_dim=15;

	IplImage* bnr=SkinSeg(src);
	Mat bnr_mat=cvarrToMat(bnr);//图像类型最好（尽量）统一一下，太乱力

	Mat edge=EdgeDtc(bnr_mat);

	Mat imcontour= Mat::zeros(edge.size(), CV_8UC3);
	curve contour=ContourExtr(edge,imcontour);

	Mat imhull = Mat::zeros(edge.size(), CV_8UC3);
	Mat imdefects = Mat::zeros(edge.size(), CV_8UC3);
	Vec4i cwdpths = HullDscr(contour, edge.size(), imhull, imdefects);

	Gesture gesture = HullDtm(cwdpths);

	char gesture_name[16] = { 0 };
	char result_name[8] = { 0 };
	NameShow(gesture, HgName, gesture_name, result_name);

	//float* Zd=FrDscr(contour,Eff_FDV_dim);

	//存储部分
	cvSaveImage(path_bnr,bnr);

	imwrite(path_edge,edge);

	imwrite(path_contour,imcontour);

	imwrite(path_hull, imhull);
	imwrite(path_defects, imdefects);

	printf("The gesture is:\n");
	printf("%s\n", gesture_name);
	printf("The result is:\n");
	printf("%s\n", result_name);

	/*FILE *fp = fopen(path_FDV, "a");
	char note[10]={0};
	sprintf(note,"%s%s",file,"：");
	fprintf(fp,note);
	for (int k = 0; k < Eff_FDV_dim; k++)
	{
		fprintf(fp, "%8f\t", Zd[k]);
	}
	fprintf(fp, "\n");
	fclose(fp);*/

	return 0;
}