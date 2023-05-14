#pragma once

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <wchar.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;
