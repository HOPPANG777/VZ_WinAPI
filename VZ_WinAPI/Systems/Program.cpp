#include "stdafx.h"
#include "Program.h"

#define CENTER_X (WIN_DEFAULT_WIDTH / 2)
#define CENTER_Y (WIN_DEFAULT_HEIGHT / 2)
#define CENTER (Vector2(CENTER_X, CENTER_Y))

Program::Program()
{
    //// 패들을 화면 하단 중앙에 배치 (예: 화면 높이의 50픽셀 위)
    //paddle = std::make_unique<Paddle>(Vector2(CENTER_X, WIN_DEFAULT_HEIGHT - 50), Vector2(150, 20), RGB(0, 255, 0));
    //
    //// 공을 화면 중앙에 배치, 초기 속도 설정
    //ball = std::make_unique<Ball>(CENTER, Vector2(200.0f, -200.0f), 10, RGB(0, 0, 0));
    //
    //InitializeBricks();
    ResetGame();
}

Program::~Program()
{
}

void Program::ResetGame()
{
    score = 0;
    lives = 3;
    bricks.clear();
    InitializeBricks();
    paddle = std::make_unique<Paddle>(Vector2(CENTER_X, WIN_DEFAULT_HEIGHT - 50), Vector2(150, 20), RGB(0, 255, 0));
	ball = std::make_unique<Ball>(CENTER, Vector2(200.0f, -200.0f), 10, RGB(0, 0, 0));
	gameState = GameState::GAME_PLAYING;
}

void Program::InitializeBricks()
{
    const int rows = 5;
    const int cols = 10;
    const int brickWidth = 100;
    const int brickHeight = 30;
    const int offsetY = 50;
    const int spacing = 5;
    const int totalWidth = cols * brickWidth + (cols - 1) * spacing;
    const int offsetX = (WIN_DEFAULT_WIDTH - totalWidth) / 2;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            Vector2 pos(offsetX + col * (brickWidth + spacing) + brickWidth / 2, offsetY + row * (brickHeight + spacing) + brickHeight / 2);
            bricks.push_back(std::make_unique<Brick>(pos, Vector2(brickWidth, brickHeight), RGB(255 - row * 40, row * 40, 150)));
        }
    }
}

void Program::Update(float deltaTime, const RECT& windowRect)
{
    if (gameState == GameState::GAME_PLAYING)
    {
        paddle->Update(deltaTime, windowRect);
        ball->Update(deltaTime, windowRect);
    
        // 패들과 공의 충돌 체크
        if (ball->CheckCollision(paddle->GetRect()))
        {
            ball->ReflectVertical();
        }

        // 벽돌과 공의 충돌 체크
        for (auto& brick : bricks)
        {
            if (brick->IsActive() && ball->CheckCollision(brick->GetRect()))
            {
                brick->Destroy();
                ball->ReflectVertical();
                score += 100;
                break; // 한 프레임에 한 벽돌만 처리
            }
        }

        bool allBroken = true;
        for (auto& brick : bricks)
        {
            if (brick->IsActive())
            {
                allBroken = false;
                break;
            }
        }

        if (allBroken) gameState = GameState::GAME_CLEAR;

        // 공이 화면 아래로 떨어지면 목숨을 차감하고 재배치
        if (ball->GetPosition().y - ball->GetRadius() > windowRect.bottom)
        {
            --lives;
            if (lives > 0)
            {
                ball = std::make_unique<Ball>(CENTER, Vector2(200.0f, -200.0f), 10, RGB(0, 0, 0));
                paddle = std::make_unique<Paddle>( Vector2(CENTER_X, WIN_DEFAULT_HEIGHT - 50), Vector2(150, 20), RGB(0, 255, 0));
            }
            else
            {
                gameState = GameState::GAME_OVER;
            }
        }
    }
    else if (gameState == GameState::GAME_OVER)
    {
        if (Input::Get()->Down('Y'))
        {
            ResetGame();
        }
        else if (Input::Get()->Down('N'))
        {
            PostQuitMessage(0);
        }
    }
    else if (gameState == GameState::GAME_OVER)
    {
        if (Input::Get()->Down('Y'))
        {
            PostQuitMessage(0);
        }
        else if (Input::Get()->Down('N'))
        {
            ResetGame();
        }
    }
}

void Program::Render(HDC hdc)
{
    if (gameState == GameState::GAME_PLAYING)
    {
        paddle->Render(hdc);
        ball->Render(hdc);
        for (auto& brick : bricks) brick->Render(hdc);

        std::wstring info = L"점수 : " + std::to_wstring(score) + L" | 남은 목숨: " + std::to_wstring(lives);
        TextOutW(hdc, 10, 10, info.c_str(), static_cast<int>(info.size()));
    }
    else if (gameState == GameState::GAME_OVER)
    {
        std::wstring line1 = L"게임 오버!";
        std::wstring line2 = L"점수 : " + std::to_wstring(score);
        std::wstring line3 = L"다시 재도전 하겠습니까? Y/N";
        int x = WIN_DEFAULT_WIDTH / 2 - 100;
        int y = WIN_DEFAULT_HEIGHT / 2 - 20;
        TextOutW(hdc, x, y - 20, line1.c_str(), static_cast<int>(line1.size()));
        TextOutW(hdc, x, y, line2.c_str(), static_cast<int>(line2.size()));
        TextOutW(hdc, x, y + 20, line3.c_str(), static_cast<int>(line3.size()));
    }
    else if (gameState == GameState::GAME_CLEAR)
    {
        std::wstring line1 = L"게임 클리어!";
        std::wstring line2 = L"점수 : " + std::to_wstring(score);
        std::wstring line3 = L"남은 목숨: " + std::to_wstring(lives);
        std::wstring line4 = L"게임을 종료하시겠습니까? Y/N";
        int x = WIN_DEFAULT_WIDTH / 2 - 100;
        int y = WIN_DEFAULT_HEIGHT / 2 - 30;
        TextOutW(hdc, x, y - 30, line1.c_str(), static_cast<int>(line1.size()));
        TextOutW(hdc, x, y - 10, line2.c_str(), static_cast<int>(line2.size()));
        TextOutW(hdc, x, y + 10, line3.c_str(), static_cast<int>(line3.size()));
        TextOutW(hdc, x, y + 30, line4.c_str(), static_cast<int>(line4.size()));
    }
}