#pragma once
#include <Windows.h>

class CBallsSettingsMonitor
{
private:
	double angle;//����
	double speed;//��������
public:
	CBallsSettingsMonitor();
	~CBallsSettingsMonitor();
	void Draw(HDC);
	void SpeedUp();
	void SpeedDown();
	void AngleUp();
	void AngleDown();
	void GetVxVy(double& vx, double& vy);
};