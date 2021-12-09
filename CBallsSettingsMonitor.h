#pragma once
#include <Windows.h>

class CBallsSettingsMonitor
{
private:
	double angle;//”гол
	double speed;//—корость
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