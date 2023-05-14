#include "pch.h"
#include "FlexiPlugCore.h"

#pragma  data_seg(".FlexiPlugCore")
WCHAR FlexiPlugCore::m_szPluginPath[1024] = { 0, };
#pragma  data_seg()
#pragma comment(linker, "/SECTION:.FlexiPlugCore,RWS")

FlexiPlugCore& FlexiPlugCore::GetInstance()
{
	static FlexiPlugCore* inst = nullptr;
	if (nullptr == inst)
		inst = new FlexiPlugCore();

	return *inst;
}

FlexiPlugCore::~FlexiPlugCore()
{
	UnLoad();
}


FlexiPlugCore::FlexiPlugCore()
{

}

void FlexiPlugCore::LoadPlugins()
{
	// 길이가 0인 경우 경로가 미설정이므로, 기본 경로를 사용한다.
	size_t nLenPluginPath = wcsnlen_s(m_szPluginPath, _countof(m_szPluginPath));
	if (nLenPluginPath <= 0)
		SetPluginPath(STR_DEFAULT_PLUGIN_PATH);

	// 경로가 없으면 만든다.
	if (false == fs::exists(fs::path(m_szPluginPath)))
		fs::create_directories(fs::path(m_szPluginPath));

	// 특정 경로를 순회하면서 존재하는 dll 파일들을 로딩 시킨다.
	for (const auto& entry : fs::directory_iterator(fs::path(m_szPluginPath)))
	{
		if (true == fs::is_regular_file(entry) && 
			0 == entry.path().extension().compare(".dll"))
		{
			HMODULE hMod = LoadLibraryW(entry.path().wstring().c_str());
			if (NULL != hMod)
			{
				BOOL bIsUnLoad = TRUE;
				FARPROC fp = GetProcAddress(hMod, "IsHostProcess");
				if (NULL != fp)
				{
					if (TRUE == reinterpret_cast<fp_IsHostProcess>(fp)())
					{
						fp = GetProcAddress(hMod, "Link");
						if (NULL != fp)
						{
							m_Links.push_back(reinterpret_cast<fp_Link>(fp));
							bIsUnLoad = FALSE;
						}
					}
				}
				
				if (TRUE == bIsUnLoad)
					FreeLibrary(hMod);
			}
		}
	}
}

void FlexiPlugCore::SetPluginPath(const WCHAR * pPath)
{
	std::wmemset(m_szPluginPath, 0x00, _countof(m_szPluginPath));
	wcscpy_s(m_szPluginPath, _countof(m_szPluginPath), pPath);
}

void FlexiPlugCore::Link(int nId)
{
	for (auto fp : m_Links)
	{
		fp(nId);
	}
}

void FlexiPlugCore::Load()
{

}

void FlexiPlugCore::UnLoad()
{
}
