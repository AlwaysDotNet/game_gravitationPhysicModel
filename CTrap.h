#pragma once
//Файл шариков
#include "CBall.h"

class CTRap
{
public:
	//Место ловушки
	double x, y;
	//Коэфициент
	double f;
	//Расстояние который действует
	double r;
	CTRap(double x, double y, double f, double r);
	virtual ~CTRap(void);
	void Draw(HDC dc);
	void Effect(CBall* ball);
};