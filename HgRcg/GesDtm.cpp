#include "ParaSet.h"

Gesture drc(Point Dweb, curve contour);

Gesture GesDtm(Vec4i cwdpths, Point Dweb, curve contour)
{
	Gesture gesture;
	int Nweb = 1;
	for (int i = 1; i < 4; i++)
	{
		if (cwdpths[i] > cwdpths[0] / 2)
		{
			Nweb++;
		}
	}

	switch (Nweb)
	{
	case 4:gesture = Palm; break;
	case 3:gesture = Ok; break;
	case 2:gesture = Check; break;
	case 1:gesture = drc(Dweb, contour); break;
	default:gesture = Illegal;
	}

	return gesture;
}

Gesture drc(Point Dweb, curve contour)
{
	Point center;
	int N = contour.size();
	int sum_x = 0, sum_y = 0;
	for (int idx = 0; idx < N; idx++)
	{
		sum_x += contour[idx].x;
		sum_y += contour[idx].y;
	}
	center.x = sum_x / N;
	center.y = sum_y / N;

	Gesture drcgs;
	//注意图像的像素是从上往下排的
	if (Dweb.y < center.y)
		drcgs = Up;
	else
		drcgs = Down;

	return drcgs;
}