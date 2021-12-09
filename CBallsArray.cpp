#include "CBallsArray.h"
#include <fstream>
//Конструктор класса 
CBallsArray::CBallsArray(int max_balls)
{
	this->count = 0;//Обнуление
	this->max_balls = max_balls;
	this->bals = new CBall * [max_balls];
	this->trap = new CTRap(200, 180, 500, 50);
}
//Деструктор класса
CBallsArray::~CBallsArray(void)
{
	for (int i = 0; i < count; i++)
	{
		delete this->bals[i];
	}
	delete[] this->bals;
}
//Метод добавление
CBall* CBallsArray::Add()
{
	if (count >= max_balls)
		return NULL;
	count++;
	bals[count - 1] = new CBall();
	return bals[count - 1];
}
void CBallsArray::SetGravityFactor(double gF)
{
	this->gF = gF;
}
//Метод отрисовки
void CBallsArray::Draw(HDC dc)
{
	for (int i = 0; i < count; i++)
		bals[i]->Draw(dc);
}
//Метод движение
void CBallsArray::Move(DWORD delta_ticks)
{

	CBall* bal1;
	CBall* bal2;
	for (int i = 0; i < count; i++)
	{
		for (int j = i+1; j < count; j++)
		{
			bal1 = this->bals[i];
			bal2 = this->bals[j];

			double cx = bal2->GetX() - bal1->GetY();
			double cy = bal2->GetY() - bal1->GetY();
           
			double cSqr = cx * cx + cy * cy;
			//Проверка на радиус
			/*
				  
		    _______r     и нужно сравнить между центрам
			*/
			if (cSqr <= ((bal1->GetR() + bal2->GetR()) * (bal1->GetR() + bal2->GetR())))
			{
				double b1Sc = bal1->GetVx() * cx + bal2->GetVx()*cy;
				double b2Sc = bal2->GetVx() * cx + bal2->GetVy()*cy;

				double b1Nvx = (cx * b1Sc) / cSqr;
				double b1Nvy = (cy * b1Sc) / cSqr;

				double b1Tvx = bal1->GetVx() - b1Nvx;
				double b1Tvy = bal1->GetVy() - b1Nvy;


				double b2Nvx = (cx * b2Sc) / cSqr;
				double b2Nvy = (cy * b2Sc) / cSqr;

				double b2Tvx = bal2->GetVx() - b2Nvx;
				double b2Tvy = bal2->GetVy() - b2Nvy;

				//Установка 
				//////////////////////////////////////
				//Если оба цветовые 
				if (bal1->GetType() && bal2->GetType())
				{
					//std::ofstream of("log.txt",std::ios_base::app);
					
					//ТОгда обмен значение
					unsigned char r1, r2, g1, g2, b1, b2;
					CColoredBall* bl1=(CColoredBall*)bals[i];
					CColoredBall* bl2 = (CColoredBall*)bals[j];
					
					bl1->GetColor(r1, g1, b1);
					bl2->GetColor(r2, g2, b2);
					//of << (int)r1 << " " << (int)g1 << " " << (int)b1 << "-" << (int)r2 << " " <<
						//(int)g2 << " " << (int)b2 << "\n";

					bl1->SetColor(r2, g2, b2);
					bl2->SetColor(r1, g1, b2);
				}
				
				
				////////////////////////////////////////
				//Реализуем столькновение по импульсу
				bal1->SetVx(b2Nvx + b1Tvx);
				bal1->SetVy(b2Nvy + b1Tvx);

				bal2->SetVx(b1Nvx + b2Tvx);
				bal2->SetVy(b1Nvy + b2Tvy);
				/////////////////////////////////////////
			}
		}
	}
	//Гравитация
	for (int i = 0; i < count; i++)
	{
		double tmpvY = bals[i]->GetVy();
		tmpvY += this->gF;
		bals[i]->SetVy(tmpvY);
		
	}
	for (int i = 0; i < count; i++)
	this->trap->Effect(bals[i]);

	for (int i = 0; i < count; i++)
		bals[i]->Move(delta_ticks);
}
//Установлние границ
void CBallsArray::SetBounds(RECT bnds)
{
	for (int i = 0; i < count; i++)
		bals[i]->SetBounds(bnds);
}
//Добавление цветовых шариков
CColoredBall* CBallsArray::AddColoredBall()
{
	if (count >= max_balls)
		return NULL;
	count++;
	bals[count - 1] = new CColoredBall();
	return (CColoredBall*)bals[count-1];
}
