#pragma once
#include "stdafx.h"

// 게임에서 활용되는 모든 오브젝트의 기본 클래스
class Object
{
public :
	Object() = default;
	virtual ~Object() = default;

public:
    // 기본 동작을 강제하기 위한 순수 가상 함수들
    virtual void Update(float deltaTime, const RECT& windowRect) = 0;
    virtual void Render(HDC hdc) = 0;
};