#include "ParaSet.h"

Vec4i HullDscr(curve contour,Size ImgSize, Mat& imhull, Mat& imdefects)
{
	int width = ImgSize.width;
	int height = ImgSize.height;
	
	//��͹��
	curve hull;
	convexHull(contour, hull, false, true);
	vector<int> hull_int;
	convexHull(contour, hull_int, false, true);

	//��ȱ��
	vector<Vec4i> defects;
	convexityDefects(contour, hull_int, defects);

	//����͹��
	cluster hull_pack;
	hull_pack.push_back(hull);
	drawContours(imhull, hull_pack, -1, Scalar(255, 255, 255), 1, 8, vector<Vec4i>());

	//���Ƹ�͹��ȱ��
	int N_defects = defects.size();
	Vec4i defect;
	int idxfront, idxrear, idxvalley, depth;
	Point front, rear, valley;
	vector<int> depths;
	int counter = 0;
	for (int i = 0; i < N_defects; i++)
	{
		defect = defects[i];

		idxfront = defect[0];
		idxrear = defect[1];
		idxvalley = defect[2];
		depth = defect[3] / 256;

		front = contour[idxfront];
		rear = contour[idxrear];
		valley = contour[idxvalley];

		//Ѱ�ҷ�ͼ��ȱ��
		if (front.x % (width - 2) && front.y % (height - 2))
		{
			//depths[counter] = depth;
			depths.push_back(depth);
			counter++;
		}

		if (depth > 0 && front.x % (width - 2) && front.y % (height - 2))
		{
			line(imdefects, front, valley, CV_RGB(0, 255, 0), 2);
			line(imdefects, rear, valley, CV_RGB(0, 255, 0), 2);

			circle(imdefects, front, 4, Scalar(255, 0, 100), 2);
			circle(imdefects, rear, 4, Scalar(255, 0, 100), 2);
			circle(imdefects, valley, 4, Scalar(100, 0, 255), 2);
		}
	}

	//����Ԥ���������
	Vec4i cwdpths;
	int N_depths = counter;
	int t;
	for (int i = 0; i < 4; i++)
	{
		for (int j = N_depths - 1; j; j--)
		{
			if (depths[j] > depths[j - 1])
			{
				t = depths[j];
				depths[j] = depths[j - 1];
				depths[j - 1] = t;
			}
		}
		cwdpths[i] = depths[i];
	}

	return cwdpths;
}