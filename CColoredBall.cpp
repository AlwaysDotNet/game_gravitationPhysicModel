#include "CColoredBall.h"

//Конструктор Цветого Шара
CColoredBall::CColoredBall(void )
{
	this->hBrush = CreateSolidBrush(RGB(0, 0, 0));
	this->r = this->g = this->b = 0;
	this->col = CBall::type::CColored;
}
//Деструктор
CColoredBall::~CColoredBall(void )
{
	DeleteBrush(this->hBrush);

}

//Установка цвета
void CColoredBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{
	DeleteBrush(this->hBrush);
	this->hBrush = CreateSolidBrush(RGB(r, g, b));
	this->r = r;
	this->g = g;
	this->b = b;
}

//Метод отрисовки
void CColoredBall::Draw(HDC dc)
{
	HBRUSH old = SelectBrush(dc, this->hBrush);
	Ellipse(dc, this->GetX() - this->GetR(), this->GetY() - this->GetR(), this->GetX() + this->GetR(), this->GetY() + this->GetR());
	SelectBrush(dc, old);
}

void CColoredBall::GetColor(unsigned char& r, unsigned char& g, unsigned char& b)
{
	r = this->r;
	g = this->g;
	b = this->b;
}
