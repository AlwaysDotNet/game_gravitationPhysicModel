#pragma once
#include <Windows.h>
#include <windowsx.h>
class CBall
{
private:
	double x, y;
	double vx, vy;
	double r;
	RECT bounds;
//Объявляем тип с цветами и бнз
protected:
	enum type { CColored, NotColored };
	type col;

public:
	CBall(void);
	virtual ~CBall(void);

	virtual void SetParams(double x, double y, double r, double vx, double vy, RECT rect);
	virtual void Draw(HDC dc);
	void Move(DWORD delta_ticks);
	void SetBounds(RECT bnds);

	double GetX()const;//Координата по x
	double GetY()const;//Координата по y
	double GetVx()const;//Скорость движение по vx
	double GetVy()const;//Скорость движение по y
	double GetR()const;//Радиус
	
	void SetVx(double vx);
	void SetVy(double vy);

	//Метод изменинеи цвета
	void SetColor(unsigned char r, unsigned char g, unsigned char b);
	//Напишим метод получение 
	void GetColor(unsigned char& r, unsigned char& g, unsigned char& b);//Оно пусто

	int  GetType()const;
};