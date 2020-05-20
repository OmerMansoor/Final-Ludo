#pragma once
#include"Position.h"
#include"graphics.h"
#include<iostream>
using namespace std;
class Player;
class Piece
{
public:	
	Player* Pl;
	int Token;
	colors Cl;
	int state;
	int BoardPosition;
	int Home;
	int End;
	int yShift;
	int Team;
	/*
		Red=4;
		Purple=9;
		Cyan=3;
		Blue=1;
		Yellow=14;
		Green=10;
	*/
	Position HomePosition;
	Position EndPosition;
	Piece(Player* P, int token,  Position Homeposition,int home,int end, int yshift = 0) :Pl(P), Token(token)
		, yShift(yshift), HomePosition(Homeposition),Home(home),End(end)
	{
		BoardPosition = -10;
		state = -1;
	}
	Piece() {}
	void InitPiece(Player* P, int token, Position Homeposition,Position Endposition, int home, int end, int yshift,colors Co,int team)
	{
		Pl = P;
		Token = token;
		yShift = yshift;
		HomePosition = Homeposition;
		EndPosition = Endposition;
		Home = home;
		End = end;
		state = -1;
		Cl = Co;
		BoardPosition = -10;
		Team = team;
	}
	void Draw(int ri, int ci, int xShift,int size = 10)
	{
		setfillstyle(SOLID_FILL, Cl);
		setcolor(BLACK);
		fillellipse(ci + xShift, ri + yShift, size, size);
		setfillstyle(SOLID_FILL, WHITE);
	}
	int Draw()
	{
		setfillstyle(SOLID_FILL, WHITE);
		fillellipse(HomePosition.c * 80 + 40, HomePosition.r * 80 + 40, 20, 20);
		setfillstyle(SOLID_FILL, Cl);
		setcolor(BLACK);
		if (state == -1)
		{
			fillellipse(HomePosition.c * 80 + 40, HomePosition.r * 80 + 40, 10, 10);
			return -1;
		}
		if (state == 1)
		{
			fillellipse(EndPosition.c * 80 + 40, EndPosition.r * 80 + 40, 10, 10);
			return -1;
		}
		if (state == 0)
		{
			return BoardPosition;
		}
	}
	void DoSomethingCrazy()
	{
		state = 0;
		BoardPosition = 3;
	}
	bool IsLegalMove(int Dice)
	{
		int n = BoardPosition + Dice;
		if (n > 55)n -= 56;
		if (state == 1) return false;
		if (state == -1 && Dice != 6) return false;
		int x;
		for (int i = 0; i < Dice; i++)
		{
			x = n - i;
			if (x < 0)x = 55;
			if (x == Home) return false;//???
		}
		return true;
	}
	void Move(int Dice)
	{
		int Temp = BoardPosition + Dice;
		if (Temp > 55) Temp -= 56;
		if (state == -1 && Dice == 6)
		{
			BoardPosition = Home;
			return;
		}
		BoardPosition = Temp;
		

	}
	void GetOutOfHome()
	{
		if (state != -1) cout << "\nERROR IN GETOUTOFHOMR!!\n";
		else
		{
			state = 0;
			BoardPosition = Home;
		}
	}
	void GoToHome()
	{
		BoardPosition = -10;
		state = -1;
		Draw();
	}
	void GoToHeaven()
	{
		state = 1;
		BoardPosition = -10;
		Draw();
	}
};

