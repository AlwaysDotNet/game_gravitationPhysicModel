#include "CBallsSettingsMonitor.h"
#include <cmath>
//

//����������� ������
CBallsSettingsMonitor::CBallsSettingsMonitor()
{
	this->angle = 45;//45 ��������
	this->speed = 50;//50x �������
}
//����������
CBallsSettingsMonitor::~CBallsSettingsMonitor()
{

}
//����� ���������
void CBallsSettingsMonitor::Draw(HDC dc)
{
	double h_speed = ((this->speed / 120) * 30) / 2;
	double r_angle = (this->angle / 180) * 3.1415;
	double x = h_speed * cos(r_angle);
	double y = h_speed * sin(r_angle);
	Rectangle(dc, 0, 0, 30, 30);
	MoveToEx(dc, (15 - x), (15 - y), NULL);
	LineTo(dc, (15 + x), (15 + y));
	Ellipse(dc, (15 + x - 2), (15 + y - 2), (15 + x + 2), (15 + y + 2));

}
//��������� �������
void CBallsSettingsMonitor::SpeedUp()
{
	if (this->speed < 120)
		speed++;
}
//�������� ������
void CBallsSettingsMonitor::SpeedDown()
{
	if (this->speed > 10)
		speed--;
}
//��������� ���� 
void CBallsSettingsMonitor::AngleUp()
{
	angle++;
	fmod(angle, 360.0);
}
void CBallsSettingsMonitor::AngleDown()
{
	angle--;
	if (angle <= 0)
		angle = 360;
}
void CBallsSettingsMonitor::GetVxVy(double& vx, double& vy)
{
	double rad_angle = (this->angle / 180.0) * 3.1415;
	vx = this->speed * cos(rad_angle);
	vy = this->speed * sin(rad_angle);
}
