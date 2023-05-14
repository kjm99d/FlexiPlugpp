#pragma once

#if FLEXIPLUGTESTPLUGIN_EXPORTS
#define FLEXIPLUGTESTPLUGIN_EXPORT __declspec(dllexport)
#else
#define FLEXIPLUGTESTPLUGIN_EXPORT __declspec(dllimport)
#endif

#if __cplusplus
extern "C" 
{
#endif

	FLEXIPLUGTESTPLUGIN_EXPORT BOOL Link(int nId);



#if __cplusplus
}
#endif
