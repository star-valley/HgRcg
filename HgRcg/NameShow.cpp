#include "ParaSet.h"

void NameShow(Gesture gesture, string HgName, string& gesture_name, string& result_name)
{
	switch (gesture)
	{
	case Palm:gesture_name = "ƽչ"; break;
	case Ok:gesture_name = "OK"; break;
	case Check:gesture_name = "�Ժ�"; break;
	case Up:gesture_name = "��ָ"; break;
	case Down:gesture_name = "��ָ"; break;
	default:gesture_name = "�Ǽ���������";
	}

	Result result = (HgName == gesture_name) ? True : False;

	result_name = result ? "��ȷ" : "����";
}