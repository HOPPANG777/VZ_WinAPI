#pragma once

#include "Objects/Rect.h"
#include "Input.h"

class Program
{
public:
	Program();
	~Program();

public:
	void Update();
	void Render();

private:
	std::unique_ptr<Rect> rect1;
	std::unique_ptr<Rect> rect2;

};

