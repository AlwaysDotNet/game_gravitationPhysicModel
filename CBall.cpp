#include "CBall.h"
CBall::CBall(void)
{
	this->col = CBall::type::NotColored;//Без цветов
}

//
CBall::~CBall(void )
{

}

//Установка
void CBall::SetParams(double x, double y, double r, double vx, double vy,RECT rect)
{
	this->x = x;
	this->y = y;
	this->r = r;
	this->vx = vx;
	this->vy = vy;
	this->bounds = rect;
}

//
void CBall::Draw(HDC dc)
{
	Ellipse(dc, x - r, y - r, x + r, y + r);
}
//
void CBall::Move(DWORD delta_ticks)
{
	
	double s_delta = ((double)delta_ticks) / 1000.0;
	if ((this->x >= bounds.right - r) && (this->vx > 0))
		this->vx = -(this->vx);
	if ((this->x <= r) && (this->vx < 0))
		this->vx = -(this->vx);
	if ((this->y >= bounds.bottom - r) && (this->vy > 0))
		this->vy = -(this->vy);
	if ((this->y <= r) && (this->vy < 0))
		this->vy = -(this->vy);
	double dx = vx * s_delta;
	double dy = vy * s_delta;
	this->x += dx;
	this->y += dy;
}
void CBall::SetBounds(RECT bnds)
{
	this->bounds = bnds;
}
//Геттеры
double CBall::GetVx()const
{
	return this->vx;
}
//
double CBall::GetVy()const
{
	return this->vy;
}
//
double CBall::GetX()const
{
	return this->x;
}
//
double CBall::GetY()const
{
	return this->y;
}
//
double CBall::GetR()const
{
	return  this->r;
}

void CBall::SetVx(double vx)
{
	this->vx = vx;
}
void CBall::SetVy(double vy)
{
	this->vy = vy;
}
//Реализуем  метод изменение цвета
//В этом классы он нечего не делает
void CBall::SetColor(unsigned char r, unsigned char g, unsigned char b)
{

}
//Получение цвета
void CBall::GetColor(unsigned char& r, unsigned char& g, unsigned char& b)
{

}

int CBall::GetType() const
{
	
		switch (col)
		{
		case type::CColored:
			return 1;
		default:
			return 0;

		}
	
}
