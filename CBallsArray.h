#pragma once
#include "CBall.h"
#include "CColoredBall.h"
#include "CTrap.h"
class CBallsArray
{
private:
	CBall** bals;//Массив шаров
	int count;//Текушый число шаров
	int max_balls;//Максимальное количество шаров
	double gF;//Гравитация
public:
	CTRap* trap;

	CBallsArray(int max_balls);
	virtual ~CBallsArray(void);

	void SetGravityFactor(double gF);
	CBall* Add();
	void Draw(HDC dc);
	void Move(DWORD delta_ticks);
	void SetBounds(RECT bnds);

	CColoredBall* AddColoredBall();
};