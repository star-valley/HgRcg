#include "ParaSet.h"

void NameShow(Gesture gesture, char* HgName, char* gesture_name, char* result_name)
{
	switch (gesture)
	{
	case Palm:strcpy(gesture_name, "ƽչ"); break;
	case Check:strcpy(gesture_name, "�Ժ�"); break;
	case Victory:strcpy(gesture_name, "ʤ��"); break;
	default:strcpy(gesture_name, "�Ǽ���������");
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
	case True:strcpy(result_name, "��ȷ"); break;
	case False:strcpy(result_name, "����"); break;
	default:strcpy(result_name, "Ĭ��");
	}

}