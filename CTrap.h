#pragma once
//���� �������
#include "CBall.h"

class CTRap
{
public:
	//����� �������
	double x, y;
	//����������
	double f;
	//���������� ������� ���������
	double r;
	CTRap(double x, double y, double f, double r);
	virtual ~CTRap(void);
	void Draw(HDC dc);
	void Effect(CBall* ball);
};