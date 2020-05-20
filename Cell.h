#pragma once
#include"Piece.h"
class Cell
{
public:
	Piece* Ps[6][4];
	int Size[6];
	Position P;
	bool IsStop;
	Cell() 
	{
		for (int i = 0; i < 6; i++)
		{
			Size[i] = 0;
			for (int j = 0; j < 4; j++)
			{
				Ps[i][j] = nullptr;
			}
		}
		IsStop = false;
	}
	void AddPeice(Piece* P, int ID)
	{
		Ps[ID][Size[ID]] = P;
		Size[ID]++;
	}
	Piece* RemovePeice(int ID)
	{
		if (Size[ID] == 0)
		{
			cout << "\n\nERROR IN REMOVE PEICE!!";
			return nullptr;
		}
		Piece* P = nullptr;
		swap(Ps[ID][Size[ID] - 1],P);
		Size[ID]--;
		return P;
	}
	void InitPosition(Position Pos)
	{
		P = Pos;
	}
	
	void Draw(bool CFH=false)
	{
		setbkcolor(BLACK);
		setfillstyle(SOLID_FILL, WHITE);
		if (!IsStop || CFH)
			bar(P.c * 80, P.r * 80, (P.c + 1) * 80 - 1, (P.r + 1) * 80 - 1);
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < Size[i]; j++)
			{
				Ps[i][j]->Draw(P.r*80,P.c*80,(j*10)+20);
			}
		}
	}
	void Highlight()
	{
		setfillstyle(SOLID_FILL, GREEN);
		bar(P.c * 80, P.r * 80, (P.c + 1) * 80 - 1, (P.r +1) * 80 - 1);
		setfillstyle(SOLID_FILL, WHITE);
	}
	void KillFrom(int ID)
	{
		if (IsStop) return;
		for (int i = 0; i < 6; i++)
		{
			if (i == ID) continue;
			if (Size[i] == 0) continue;
			if (Ps[ID][0]->Team == Ps[i][0]->Team) continue;
			if (Size[ID] < Size[i]) continue;
			for (int j = 0; j < Size[i]; j++)
			{
				Ps[i][j]->GoToHome();
				Ps[i][j] = nullptr;
			}
			Size[i] = 0;
		}
		Draw();
	}
};

