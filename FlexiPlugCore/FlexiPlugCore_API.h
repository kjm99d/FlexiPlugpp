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
		 * �÷������� ���� ���μ����� �޸𸮷� �ε��Ų��.
		 */
		FLEXIPLUGCORE_API int Load();
		/**
		 * �ε��ϰ��� �ϴ� �÷������� ��θ� �����Ѵ�.
		 */
		FLEXIPLUGCORE_API void SetPath(WCHAR* pPath);

		FLEXIPLUGCORE_API void Link(int nId);
	};

#if __cplusplus
}
#endif