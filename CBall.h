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
//��������� ��� � ������� � ���
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

	double GetX()const;//���������� �� x
	double GetY()const;//���������� �� y
	double GetVx()const;//�������� �������� �� vx
	double GetVy()const;//�������� �������� �� y
	double GetR()const;//������
	
	void SetVx(double vx);
	void SetVy(double vy);

	//����� ��������� �����
	void SetColor(unsigned char r, unsigned char g, unsigned char b);
	//������� ����� ��������� 
	void GetColor(unsigned char& r, unsigned char& g, unsigned char& b);//��� �����

	int  GetType()const;
};