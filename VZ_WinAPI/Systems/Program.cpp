#include "stdafx.h"
#include "Program.h"

Program::Program()
{
	rect1 = std::make_unique<Rect>(CENTER, Vector2(100, 100), RGB(0, 0, 255));
	rect2 = std::make_unique<Rect>(CENTER + Vector2(200, -200), Vector2(100, 100), RGB(255, 0, 0));

	rect1->SetMaxSpeed(500.0f);
	rect2->SetMaxSpeed(500.0f);
}

Program::~Program()
{

}

void Program::Update()
{
	rect1->ResetKeyCount();

	if (Input::Get()->Press('W'))
	{
		rect1->AddKeyCount();
		rect1->Move({ 0.0f, -rect1->GetSpeed() });
	}
	if (Input::Get()->Press('S'))
	{
		rect1->AddKeyCount();
		rect1->Move({ 0.0f, rect1->GetSpeed() });
	}
	if (Input::Get()->Press('A'))
	{
		rect1->AddKeyCount();
		rect1->Move({ -rect1->GetSpeed(), 0.0f });
	}
	if (Input::Get()->Press('D'))
	{
		rect1->AddKeyCount();
		rect1->Move({ rect1->GetSpeed(), 0.0f });
	}

	if (rect2->CheckIntersect(Input::Get()->GetMousePos()) && Input::Get()->Press(VK_LBUTTON))
	{
		rect2->SetPosition(Input::Get()->GetMousePos());
		rect2->SetColor(RGB(255, 0, 255));
	}

	if (rect1->CheckIntersect(*rect2))
	{
		rect1->SetColor(RGB(0, 255, 255));
		rect2->SetColor(RGB(255, 255, 0));
	}
	else
	{
		rect1->SetColor(RGB(255, 0, 0));
		rect2->SetColor(RGB(0, 0, 255));
	}

	rect1->Update();
	rect2->Update();
}

void Program::Render()
{
	rect1->Render();
	rect2->Render();
}
