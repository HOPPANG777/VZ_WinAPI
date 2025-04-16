#pragma once

class Time
{
	DECLARE_SINGLETON(Time);

public:
	void Update();
	
public:
	float GetDeltaTime() { return deltaT * deltaScale; }
	UINT GetFPS() const { return fps; }
	double GetWorldTime() const { return worldTime; }
	
public:
	void CheckTime() 
	{
		std::cout << "FPS : " << fps << ", DeltaTime : " << deltaT << ", WorldTime" << worldTime << '\n';;
	}

private:
	std::chrono::steady_clock::time_point currentTime;
	std::chrono::steady_clock::time_point lastTime;

	double deltaT = 0;
	float deltaScale = 1.0f;

	unsigned int fps = 0;
	double worldTime = 0;

	unsigned int frameCount = 0;
	double fpsTimeElapsed = 1.0f / 60.0f;
};