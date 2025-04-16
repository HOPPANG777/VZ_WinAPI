#pragma once

#include "Utilities/Vector.h"

#define MAX_INPUT_KEY 256

class Input
{
	DECLARE_SINGLETON(Input);

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS
	};

public:
	void Update();

	void InputProc(UINT message, LPARAM lParam);

public:
	bool Down(const DWORD key) const { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(const DWORD key) const { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(const DWORD key) const { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }
	bool DblClk(const DWORD key) const { return isDblClk; }

public:
	Vector2 GetMousePos() const { return mousePos; }

private:
	Vector2 mousePos;

	std::array<unsigned char, MAX_INPUT_KEY> keyState = { 0 };
	std::array<unsigned char, MAX_INPUT_KEY> keyOldState = { 0 };
	std::array<unsigned char, MAX_INPUT_KEY> keyMap = { 0 };

	bool isDblClk = false;

};

