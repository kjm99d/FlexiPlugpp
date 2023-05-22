#include "pch.h"
#include "FlexiPlugCore.h"

#pragma  data_seg(".FlexiPlugCore")
WCHAR FlexiPlugCore::m_szPluginPath[1024] = { 0, };
WCHAR FlexiPlugCore::m_szModulePrefix[512] = { 0, };
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
	Load();
}

BOOL FlexiPlugCore::hasFilePrefix(const std::wstring& strFilePath)
{
	BOOL bResult = FALSE;

	auto strFileName = fs::path(strFilePath).filename().wstring();
	auto strPrefix = std::wstring(m_szModulePrefix);

	if (static_cast<size_t>(0) <= strPrefix.length())
	{
		std::transform(strFileName.begin(), strFileName.end(), strFileName.begin(), ::tolower);
		std::transform(strPrefix.begin(), strPrefix.end(), strPrefix.begin(), ::tolower);

		if (static_cast<size_t>(0) == strFileName.find(strPrefix))
		{
			bResult = TRUE;
		}
	}

	return bResult; // 접두어가 없는 경우 false 반환
}

BOOL FlexiPlugCore::IsBypassModule(const WCHAR* pModulePath)
{
	BOOL bIsBypass = TRUE;

	// 이미 로딩된 모듈은 로딩하지 않도록 수정
	if (NULL == GetModuleHandle(pModulePath))
		bIsBypass = FALSE;
	

	return bIsBypass;
}

BOOL FlexiPlugCore::AddPluginModule(const WCHAR* pModulePath)
{
	BOOL bIsPluginModule = FALSE;
	if (NULL != pModulePath)
	{
		HMODULE hMod = LoadLibraryW(pModulePath);
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
						m_Links.push_back({ hMod, fp });
						bIsUnLoad = FALSE;
						bIsPluginModule = TRUE;
					}
				}
			}

			if (TRUE == bIsUnLoad)
				FreeLibrary(hMod);
		}
	}

	return bIsPluginModule;
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
			const WCHAR* pModulePath = entry.path().wstring().c_str();
			if (FALSE == IsBypassModule(pModulePath))
			{
				if (TRUE == hasFilePrefix(pModulePath) && TRUE == AddPluginModule(pModulePath))
				{
					// 플러그인 모듈인 경우
				}
				else
				{
					// 플러그인 모듈이 아닌 경우
				}
			}
		}
	}
}

void FlexiPlugCore::SetPluginPath(const WCHAR * pPath)
{
	std::wmemset(m_szPluginPath, 0x00, _countof(m_szPluginPath));
	wcscpy_s(m_szPluginPath, _countof(m_szPluginPath), pPath);
}

void FlexiPlugCore::SetModulePrefix(const WCHAR* pPrefix)
{
	std::wmemset(m_szModulePrefix, 0x00, _countof(m_szModulePrefix));
	wcscpy_s(m_szModulePrefix, _countof(m_szModulePrefix), pPrefix);
}

void FlexiPlugCore::Link(int nId)
{
	for (auto info : m_Links)
	{
		reinterpret_cast<fp_Link>(info.fp)(nId);
	}
}

void FlexiPlugCore::Load()
{
	// Empty Function ...
}

void FlexiPlugCore::UnLoad()
{
	for (auto info : m_Links)
	{
		FreeLibrary(info.hModule);
	}
}
