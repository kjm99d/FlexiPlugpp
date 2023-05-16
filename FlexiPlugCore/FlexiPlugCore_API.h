#pragma once
#include "FlexiPlugCore.h"

#if FLEXIPLUGCORE_EXPORTS
#define FLEXIPLUGCORE_API __declspec(dllexport)
#else
#define FLEXIPLUGCORE_API __declspec(dllimport)
#endif

#if __cplusplus
extern "C" {
#endif

	namespace FlexiPlugCore_API
	{
		typedef int(*FP_Load)();
		typedef void(*FP_SetPath)(WCHAR*);
		typedef void(*FP_Link)(int);

		/**
		 * 플러그인을 현재 프로세스의 메모리로 로드시킨다.
		 */
		FLEXIPLUGCORE_API int Load();
		/**
		 * 로드하고자 하는 플러그인의 경로를 설정한다.
		 */
		FLEXIPLUGCORE_API void SetPath(WCHAR* pPath);

		FLEXIPLUGCORE_API void Link(int nId);
	};

#if __cplusplus
}
#endif