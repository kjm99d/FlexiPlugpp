#include "pch.h"
#include "TestPlugin.h"

BOOL Link(int nId)
{
	switch (nId)
	{
	case 1:
		MessageBox(NULL, L"1", NULL, NULL);
	default:
		break;
	}

	return TRUE;
}
