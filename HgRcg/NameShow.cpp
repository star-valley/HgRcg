#include "ParaSet.h"

void NameShow(Gesture gesture, char* HgName, char* gesture_name, char* result_name)
{
	switch (gesture)
	{
	case Palm:strcpy(gesture_name, "平展"); break;
	case Check:strcpy(gesture_name, "对号"); break;
	case Victory:strcpy(gesture_name, "胜利"); break;
	default:strcpy(gesture_name, "非集合内手势");
	}
	Result result;
	if (!strcmp(HgName, gesture_name))
	{
		result = True;
	}
	else
	{
		result = False;
	}
	switch (result)
	{
	case True:strcpy(result_name, "正确"); break;
	case False:strcpy(result_name, "错误"); break;
	default:strcpy(result_name, "默认");
	}

}