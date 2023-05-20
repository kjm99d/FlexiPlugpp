 # 📌FlexiPlugpp

`FlexiPlugpp` 프로젝트는 C++ 기반의 완성된 기본 프로젝트 구조에서 소스코드의 큰 수정 없이 프로젝트의 기능을 확장시키고자 만들어진 라이브러리입니다.

## ❓**사용방법**

1. `FlexiPlugCore` 프로젝트를 빌드합니다.
2. 빌드된 파일들을 자신의 프로젝트에 링크 시킵니다.
3. 이후 추가적으로 확장시키고자 하는 모듈을 만듭니다.
   
    `FlexiPlug_TestPlugin` 프로젝트를 참고하여 만듭니다.
4. 자신의 프로젝트에서 이벤트를 등록합니다.

위 과정을 전부 마친 후 프로그램을 실행하면 원하는 시점에 이벤트가 발생하면 연관 모듈에게 이벤트를 전달하고,   
해당 모듈에 등록된 기능을 수행합니다.
    

## 📖**예제**

- 확장 플러그인을 만드는 방법
  
    확장시키고자하는 플러그인의 소스코드를 작성하는 방법
    
    Export 함수를 등록해줍니다.
    
    ```cpp
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
    
        FLEXIPLUGTESTPLUGIN_EXPORT BOOL IsHostProcess();
        FLEXIPLUGTESTPLUGIN_EXPORT BOOL Link(int nId);
    
    #if __cplusplus
    }
    #endif
    
    ```
    
    ```cpp
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
    
    ```
    
    Link 부분에 원하는 동작을 등록합니다.
    
    위 예제 소스코드에서는 이벤트 ID값이 `1` 인 값에 대하여 메세지박스를 출력하는 예제를 나타납니다.
    
    이후 빌드된 플러그인 DLL 파일을 `C:\Windows\FlexiPlug` 경로에 복사합니다.
    
- 프로그램에 확장 플러그인을 연결시키는 방법
  
    확장 플러그인을 연결시키는 방법
    
    ```cpp
    #include <FlexiPlugCore_API.h>
    #if _WIN64
    #pragma comment(lib, "FlexiPlugCorex64.lib")
    #else
    #pragma comment(lib, "FlexiPlugCore.lib")
    #endif
    
    int main(int argc, const char* argv[])
    {
        MessageBox(NULL, L"Program Starting ...", NULL, MB_OK);
        FlexiPlugCore_API::Load();
        FlexiPlugCore_API::Link(1);
    
        return 0;
    }
    ```
    
    위 코드는 FlexiPlugCore 라이브러리를 로드하고, 로드된 라이브러리에 `1` 이라는 이벤트값을 전달하여 확장 플러그인에 기능을 수행하도록합니다.
