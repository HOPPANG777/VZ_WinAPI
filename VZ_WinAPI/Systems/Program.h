#pragma once

#include "Objects/Paddle.h"
#include "Objects/Ball.h"
#include "Objects/Brick.h"

#include "Systems/Input.h"
#include "Systems/Time.h"

#include "Utilities/Vector.h"
#include "Utilities/APIFuncs.h"

class Paddle;
class Ball;
class Brick;

class Program
{
	enum class GameState
	{
		GAME_PLAYING = 0,
		GAME_OVER,
		GAME_CLEAR
	};

public:
	Program();
	~Program();

public:
	void Update(float deltaTime, const RECT& windowRect);
	void Render(HDC hdc);

private:
	std::unique_ptr<Paddle> paddle;
	std::unique_ptr<Ball> ball;
	std::vector<std::unique_ptr<Brick>> bricks;

	int score = 0;
	int lives = 3;

	GameState gameState = GameState::GAME_PLAYING;

private:
	void ResetGame();

private:
	void InitializeBricks();

};

