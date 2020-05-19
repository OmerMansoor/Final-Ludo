#pragma once
#include"Dice.h"
#include"Board.h"
#include"Player.h"
#include"Position.h"
#include"graphics.h"
#include"Piece.h"
#include<time.h>
#include<iostream>
using namespace std;

class Ludo
{
private:
	Player* Pl;
	Position SP;
	Position EP;
	int NOP;
	int NOT;
	int Turn;
	bool TeamMode;
	Dice D;
	int PlayersCompleted = 0;

public:
	Ludo() 
	{
		srand(time(0));
		Turn = rand() % 6;
	}
	Board B;
	void PieceSelection(int &SR, int &SC);
	void DestinationSelection(int SR,int SC,int& ER, int& EC);
	void DrawPieces();
	bool IsHomeSelection(int R, int C);
	void Select(int& R, int& C);
	void Init();
	void InitPeices();
	void InitRed();
	void InitPurple();
	void InitCyan();
	void InitBlue();
	void InitYellow();
	void InitGreen();
	void InitAll();
	void Play();
	void DiceRollCommand(int R, int C);
	void RefreshStops();
	int RowCol2Index(int, int);
	void TurnChange();
	void TurnDisplay(int,int);
	bool GameEnd();
	bool AnyMovePossible();
	void DisplayResults();
	bool IsValidSelection(int R,int C);
	bool IsValidDestination(int,int,int,int);
	void DisplayResult();
	void CompletedAll(Player);
	void DisplayElipse();
	void DoSomethingCrazy();

};

