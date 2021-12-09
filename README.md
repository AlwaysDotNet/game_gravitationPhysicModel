# game_gravitationPhysicModel

Столькновение тел Физическая модел
(uz)->(Jismalr impulsi)
![image](https://user-images.githubusercontent.com/95248609/145459625-bc7470e3-e809-4035-99d3-ee355aae79c7.png)

Закон импульса и моделеривание в программирование
![image](https://user-images.githubusercontent.com/95248609/145459887-52825580-1e46-4892-a08f-9191b438e402.png)

	double xDist = this->x - ball->GetX();
	double yDist = this->y - ball->GetY();

	double xDistSqr = xDist * xDist;
	double yDistSqr = yDist * yDist;

	double distSqr = xDistSqr + yDistSqr;

	double dist = sqrt(distSqr);

	if (dist > this->r)
	{
		return;
	}

	if (distSqr < 0.6)
		distSqr = 0.6;

	double xCoef = (this->f * (xDist / dist)) / distSqr;
	double yCoef = (this->f * (yDist / dist)) / distSqr;

	double tmpVx = ball->GetVx();
	tmpVx += xCoef;
	ball->SetVx(tmpVx);

	double tmpVy = ball->GetVy();
	tmpVy += xCoef;
	ball->SetVy(tmpVy);

(uz)->Jismlar bir biriga urilgandan keyingi holat Impulsn qonuni asosida
Кому то пригодится 
(uz) Kimgadir kerak bulib qoladi
