// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#endif

#pragma once

#include "Utilities/targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>
// C 런타임 헤더 파일입니다.
#include <cassert>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <chrono>
#include <string>
#include <memory>
#include <array>

#define WIN_DEFAULT_WIDTH 1280
#define WIN_DEFAULT_HEIGHT 720

#define CENTER_X (WIN_DEFAULT_WIDTH / 2)
#define CENTER_Y (WIN_DEFAULT_HEIGHT / 2)
#define CENTER (Vector2(CENTER_X, CENTER_Y))

#define DECLARE_SINGLETON(CLASS_NAME)						\
private:													\
CLASS_NAME();												\
~CLASS_NAME();												\
public:														\
CLASS_NAME(const CLASS_NAME& other) = delete;				\
CLASS_NAME& operator=(const CLASS_NAME& other) = delete;	\
CLASS_NAME(const CLASS_NAME&& other) = delete;				\
CLASS_NAME& operator=(const CLASS_NAME&& other) = delete;	\
public:														\
static CLASS_NAME* Get()									\
{															\
	static CLASS_NAME instance;								\
	return &instance;										\
}

//ExternGlobals
extern float gWinWidth;
extern float gWinHeight;
extern HWND gHandle;
extern HDC gHDC;