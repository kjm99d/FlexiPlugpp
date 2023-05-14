#include "pch.h"
#include "FlexiPlugCore_API.h"

int FlexiPlugCore_API::Load()
{
    FlexiPlugCore::GetInstance().LoadPlugins();
    return 0;
}

void FlexiPlugCore_API::SetPath(WCHAR* pPath)
{
    FlexiPlugCore::GetInstance().SetPluginPath(pPath);
}

void FlexiPlugCore_API::Link(int nId)
{
    FlexiPlugCore::GetInstance().Link(nId);
}
