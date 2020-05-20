#include "Dice.h"
#include<time.h>
#include "graphics.h"
#include<iostream>
#include<windows.h>

using namespace std;




void Dice::RollDice(int r, int c, bool Try)
{
	if (Try)
	{
		Ds[0] = Ds[1] = Ds[2] = 0;
		Ds[0] = 6;
		Ds[1] = 12;
		Ds[2] = 1;

		size = 3;
		UpdateDiceValues(r, c);
		return;
	}
	Ds[0] = Ds[1] = Ds[2] = 0;
	srand(time(0));
	int t = rand() % 8 + 2;
	for (int i = 0; i < t; i++)
	{
		Ds[0] = (rand() % 6) + 1;
		UpdateDiceValues(r,c);
		delay(500);
	}
	if (Ds[0] == 6)
	{
		t = rand() % 8 + 2;
		for (int i = 0; i < t; i++)
		{
			Ds[1] = (rand() % 6) + 1;
			UpdateDiceValues(r, c);
			delay(500);

		}
		if (Ds[1] == 6)
		{
			t = rand() % 8 + 2;
			for (int i = 0; i < t; i++)
			{
				Ds[2] = (rand() % 6) + 1;
				UpdateDiceValues(r, c);
				delay(500);
			}
			size = 3;
			if (Ds[2] == 6)
			{
				Ds[0] = Ds[1] = Ds[2] = 0;
				size = 0;
			}
		}
		else { Ds[2] = 0; size = 2; }
	}
	else { Ds[1] = Ds[2] = 0; size = 1; }
	UpdateDiceValues(r, c);
}
void Dice::PrintDiceAt(int ri, int ci)
{
	//int ri = 5, ci = 4;
	setcolor(GREEN);
	setfillstyle(SOLID_FILL, CYAN);
	--ci;
	bar(ci * 80, ri * 80, (ci + 1) * 80 - 1, (ri + 1) * 80 - 1);
	++ci;
	bar(ci * 80, ri * 80, (ci + 1) * 80 - 1, (ri + 1) * 80 - 1);
	++ci;
	bar(ci * 80, ri * 80, (ci + 1) * 80 - 1, (ri + 1) * 80 - 1);
	ci--;
	ri++;
	setfillstyle(SOLID_FILL, 1);
	bar(ci * 80, ri * 80, (ci + 1) * 80, (ri + 1) * 80);
	setbkcolor(1);
	ri++;
	outtextxy(ci*80 + 25,ri*80 - 20, "Roll");
}
void Dice::UpdateDiceValues(int r,int c)
{
	char Text[50];
	settextstyle(4, 0, 4);
	setbkcolor(CYAN);

	sprintf(Text, "%d", Ds[0]);
	outtextxy((c-1)*80 + 24, r*80 + 24, Text);

	sprintf(Text, "%d", Ds[1]);
	outtextxy(c*80 + 24, r*80 + 24, Text);

	sprintf(Text, "%d", Ds[2]);
	outtextxy((c+1)*80 + 24,r*80 + 24, Text);
}

//int main2()
//{
//	int R = 0, C = 0;
//	initwindow(2500, 800, "Ludo");
//	PrintBoxes();
//
//	do
//	{
//		Select(R, C);
//		if ((R >= 6 && R <= 7) && (C >= 7 && C <= 8))
//			RollDice();
//	} while (true);
//
//
//
//	system("pause");
//	return 0;
//}