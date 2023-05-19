#pragma once
#include <Windows.h>
#include <vector>

#if _WIN64
constexpr const WCHAR* STR_CURRENT_MODULE_NAME = L"FlexiPlugCorex64.dll";
#else
constexpr const WCHAR* STR_CURRENT_MODULE_NAME = L"FlexiPlugCore.dll";
#endif

constexpr const WCHAR* STR_DEFAULT_PLUGIN_PATH = L"C:\\Windows\\FlexiPlug\\";
typedef BOOL(*fp_IsHostProcess)();
typedef BOOL(*fp_Link)(int nId);

class FlexiPlugCore;
class FlexiPlugCore
{
private:
	typedef struct _INFO_FUNCTION
	{
		HMODULE hModule;
		FARPROC fp;
	} INFO_FUNCTION;
public:
	static FlexiPlugCore& GetInstance();
	~FlexiPlugCore();

private:
	FlexiPlugCore();

private:
	BOOL IsBypassModule(const WCHAR * pModulePath);
	BOOL AddPluginModule(const WCHAR* pModulePath);

public:
	void LoadPlugins();
	void SetPluginPath(const WCHAR* pPath);
	void Link(int nId);

private:
	void Load();
	void UnLoad();

	std::vector<INFO_FUNCTION> m_Links;


public:
	static WCHAR m_szPluginPath[1024];
};