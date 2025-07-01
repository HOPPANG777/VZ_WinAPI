#include "stdafx.h"
#include "Program.h"

#define CENTER_X (WIN_DEFAULT_WIDTH / 2)
#define CENTER_Y (WIN_DEFAULT_HEIGHT / 2)
#define CENTER (Vector2(CENTER_X, CENTER_Y))

Program::Program()
{
    const int totalWidth = cols * brickWidth + (cols - 1) * spacing;
    const int offsetX = (WIN_DEFAULT_WIDTH - totalWidth) / 2;
    paddle->Update(deltaTime, windowRect);
            score += 100;
    // 공이 화면 아래로 떨어지면 목숨을 차감하고 재배치
        --lives;
        if (lives > 0)
        {
            ball = std::make_unique<Ball>(CENTER, Vector2(200.0f, -200.0f), 10, RGB(0, 0, 0));
            paddle = std::make_unique<Paddle>(Vector2(CENTER_X, WIN_DEFAULT_HEIGHT - 50), Vector2(150, 20), RGB(0,255,0));
        }
        else
        {
            lives = 3;
            score = 0;
            bricks.clear();
            InitializeBricks();
            ball = std::make_unique<Ball>(CENTER, Vector2(200.0f, -200.0f), 10, RGB(0, 0, 0));
            paddle = std::make_unique<Paddle>(Vector2(CENTER_X, WIN_DEFAULT_HEIGHT - 50), Vector2(150, 20), RGB(0,255,0));
        }
    std::wstring info = L"Score: " + std::to_wstring(score) + L" Lives: " + std::to_wstring(lives);
    TextOutW(hdc, 10, 10, info.c_str(), info.size());
    
    InitializeBricks();
}

Program::~Program()
{
}

void Program::InitializeBricks()
{
    const int rows = 5;
    const int cols = 10;
    const int brickWidth = 100;
    const int brickHeight = 30;
    const int offsetX = 50;
    const int offsetY = 50;
    const int spacing = 5;

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
    paddle->Update(deltaTime);
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
            break; // 한 프레임에 한 벽돌만 처리
        }
    }

    // 공이 아래로 떨어지면 (예: windowRect.bottom 넘어가면) 게임 오버 처리 또는 공 초기화
    if (ball->GetPosition().y - ball->GetRadius() > windowRect.bottom)
    {
        // 예시로, 공을 화면 중앙으로 재배치
        ball = std::make_unique<Ball>(CENTER, Vector2(200.0f, -200.0f), 10, RGB(0, 0, 0));
    }
}

void Program::Render(HDC hdc)
{
    paddle->Render(hdc);
    ball->Render(hdc);
    for (auto& brick : bricks)
    {
        brick->Render(hdc);
    }
}