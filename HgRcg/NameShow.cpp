#include "ParaSet.h"

void NameShow(Gesture gesture, string HgName, string& gesture_name, string& result_name)
{
	switch (gesture)
	{
	case Palm:gesture_name = "平展"; break;
	case Ok:gesture_name = "OK"; break;
	case Check:gesture_name = "对号"; break;
	case Up:gesture_name = "上指"; break;
	case Down:gesture_name = "下指"; break;
	default:gesture_name = "非集合内手势";
	}

	Result result = (HgName == gesture_name) ? True : False;

	result_name = result ? "正确" : "错误";
}