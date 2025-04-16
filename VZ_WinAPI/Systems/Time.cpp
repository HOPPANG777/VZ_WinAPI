#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	currentTime = std::chrono::steady_clock::now();
	lastTime = currentTime;
}

Time::~Time()
{

}

void Time::Update()
{
	lastTime = currentTime;
	currentTime = std::chrono::steady_clock::now();
	std::chrono::duration<double> gap = currentTime - lastTime;
	deltaT = gap.count();

	worldTime += deltaT;

	fpsTimeElapsed += deltaT;
	frameCount++;
	if (fpsTimeElapsed >= 1.0f)
	{
		fpsTimeElapsed--;
		fps = frameCount;
		frameCount = 0;
		CheckTime();
	}
}
