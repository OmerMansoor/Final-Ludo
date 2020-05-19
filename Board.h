#pragma once
#include"Cell.h"
#include"graphics.h"
#include"Piece.h"
#include"Dice.h"
#include<iostream>
using namespace std;

class Board
{
public:
	Cell Cs[56];
	Board() 
	{
		int r, c;
		for (int i = 0; i < 56; i++)
		{
			Index2RowCol(i, r, c);
			Cs[i].InitPosition(Position(r, c));
		}
		int A[] = { 0, 1, 7, 8, 16, 17, 28, 29, 37, 38, 44, 45 };
		for (int i = 0; i < 12; i++)
		{
			Cs[A[i]].IsStop = true;
		}
	}
	void Index2RowCol(int Index, int& r, int& c)
	{
		if (Index <= 19)
		{
			r = 0;
			c = Index;
		}
		else if (Index <= 28)
		{
			r = Index - 19;
			c = 19;
		}
		else if (Index <= 47)
		{
			r = 9;
			c = 47 - Index;
		}
		else if (Index <= 55)
		{
			r = 56 - Index;
			c = 0;
		}
	}
	void Display()
	{

		for (int ri = 0; ri < 20; ri++)
		{
			for (int ci = 0; ci < 10; ci++)
			{
				if (ri == 0 || ri == 19 || ci == 0 || ci == 9)
					bar(ri * 80, ci * 80, (ri + 1) * 80 - 1, (ci + 1) * 80 - 1);
			}
		}
		setfillstyle(SOLID_FILL, 4);	//Red
		bar(80, 80, 239, 239);

		setfillstyle(SOLID_FILL, 1);    //Blue
		bar(80, 560, 239, 719);

		setfillstyle(SOLID_FILL, 2);	//	Green
		bar(17 * 80, 560, 19 * 80 - 1, 719);
		

		setfillstyle(SOLID_FILL, 3);     //cyan
		bar(1360, 80, 1519, 239);
		

		setfillstyle(SOLID_FILL, 5);	//purple
		bar(640, 80, 799, 239);
		

		setfillstyle(SOLID_FILL, 6);		// yelllow
		bar(640, 560, 799, 719);

		//Homes
		setfillstyle(4, 4);	//Red stay
		bar(80, 0, 159, 79);
		setfillstyle(4, 4);
		bar(10, 10, 70, 70);
		setfillstyle(4, 1);	//Blue stay
		bar(160, 9 * 80, 239, 799);
		setfillstyle(4, 1);
		bar(250, 730, 309, 789);

		setfillstyle(4, 2);	//	Green //Stay
		bar(18 * 80, 800, 19 * 80 - 1, 719);
		setfillstyle(4, 2);
		bar(19 * 80 + 10, 9 * 80 + 10, 20 * 80 - 10, 10 * 80 - 10);
		setfillstyle(4, 3);	//cyan Stay
		bar(17 * 80, 0, 18 * 80 - 1, 79);
		setfillstyle(4, 3);
		bar(16 * 80 + 10, 10, 17 * 80 - 10, 70);

		setfillstyle(4, 5);	//Purple Stay
		bar(640, 0, 719, 79);
		setfillstyle(4, 5);
		bar(570, 10, 630, 70);

		setfillstyle(4, 6);	//Yellow Stop
		bar(720, 800, 799, 719);
		setfillstyle(4, 6);
		bar(10 * 80 + 10, 9 * 80 + 10, 11 * 80 - 10, 10 * 80 - 10);
	}
	void DisplayCells()
	{
		for (int i = 0; i < 56; i++)
		{
			Cs[i].Draw();
		}
	}
	void DisplayCells(int start, int end)
	{
		Cs[start].Draw();
		Cs[end].Draw();
	}
	void Highlight(int Start,int ID,const Dice& D)
	{
		int End[3];
		int m_size = 0;
		int x;
		for (int i = 0; i < D.size; i++)
		{
			x = D.Ds[i] + Start;
			if (x >= 56)x -= 56;
			if (Cs[Start].Ps[ID][0]->state == 0)
			{
				if (Cs[Start].Ps[ID][0]->IsLegalMove(D.Ds[i]))
				{
					End[m_size] = x;
					m_size++;
				}
			}
		}
		for (int i = 0; i < m_size; i++)
		{
			Cs[End[i]].Highlight();
		}
	}
	void UnHighlight(int Start, int ID, Dice D)
	{
		int End[3];
		int m_size = 0;
		int x;
		for (int i = 0; i < D.size; i++)
		{
			x = D.Ds[i] + Start;
			if (x >= 56)x -= 56;
			if (Cs[Start].Ps[ID][0]->IsLegalMove(D.Ds[i]))
			{
				End[m_size] = x;
				m_size++;
			}
		}
		for (int i = 0; i < m_size; i++)
		{
			Cs[End[i]].Draw(true);
		}
	}
	void Move(int Start, int End,int ID, Dice& D)
	{
		Piece* Temp;
		int T = End;
		Temp=Cs[Start].RemovePeice(ID);
		if (T == Temp->End) 
		{
			Temp->GoToHeaven();
			Cs[Start].Draw();
			if (End < Start) End += 56;
			D.RemoveNum(End - Start);
			return;
		}
		Cs[End].AddPeice(Temp, ID);
		Temp->BoardPosition = End;
		if (End < Start) End += 56;
		D.RemoveNum(End - Start);
		Cs[T].KillFrom(ID);
		Cs[Start].Draw();
		Cs[T].Draw();
	}
};

