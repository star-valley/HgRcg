#include "ParaSet.h"

Gesture HullDtm(Vec4i cwdpths)
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
	case 2:gesture = Check; break;
	case 1:gesture = Up; break;
	default:gesture = Illegal;
	}

	return gesture;
}