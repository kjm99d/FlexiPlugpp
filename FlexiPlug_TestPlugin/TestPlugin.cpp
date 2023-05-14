#include "pch.h"
#include "TestPlugin.h"

BOOL IsHostProcess()
{
	const std::vector<std::wstring> vecHostProcess = {
		// 호스트 프로세스로 지정될 프로세스 정보를 기입합니다.
		// 해당 프로세스에 인젝션이 됩니다.
	};

	WCHAR szProcessName[1024] = { 0, };
	GetModuleFileNameW(NULL, szProcessName, _countof(szProcessName));
	PathStripPathW(szProcessName);

	for (auto strHostProcess : vecHostProcess)
	{
		if (0 == _wcsicmp(szProcessName, strHostProcess.c_str()))
		{
			return TRUE;
		}
	}

	return FALSE;
}

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
