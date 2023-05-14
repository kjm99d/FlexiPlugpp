#pragma once
#include <Windows.h>
#include <vector>

constexpr const WCHAR* STR_DEFAULT_PLUGIN_PATH = L"C:\\Windows\\FlexiPlug\\";
typedef BOOL(* fp_Link)(int nId);

class FlexiPlugCore;
class FlexiPlugCore
{
public:
	static FlexiPlugCore& GetInstance();
	~FlexiPlugCore();

private:
	FlexiPlugCore();

public:
	void LoadPlugins();
	void SetPluginPath(const WCHAR* pPath);
	void Link(int nId);

private:
	void Load();
	void UnLoad();

	std::vector<fp_Link> m_Links;

public:
	static WCHAR m_szPluginPath[1024];
};