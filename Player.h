#include<iostream>
#include"Team.h"
#include"Piece.h"
#include<string>
using namespace std;

class Ludo;
class Player
{
public:
	string name;
	Team* T;
	int Rank;
	Piece Ps[4];
	int ID;
	Player() {}
	Player(int PlayerID, string name_) :ID(PlayerID), name(name_) {}
	Player(int PlayerID, string name_, Team* Team) :ID(PlayerID), name(name_), T(Team) {}
	Piece* PieceWithHomeAt(int R, int C)
	{
		for (int i = 0; i < 4; i++)
		{
			if (Ps[i].HomePosition == Position(R, C)) return &Ps[i];
		}
		cout << "\nERROR IN PIECEWITHHOMEAT!!!\n";
	}
	void InitPlayer(int PlayerID, string name_,Team *t)
	{
		ID = PlayerID;
		name = name_;
		T = t;
		Rank = 0;
	}
	int CompletedPieces()
	{
		int Cp = 0;
		for (int i = 0; i < 4; i++)
		{
			if (Ps[i].state ==1)
				Cp++;
		}
		return Cp;
	}
	bool IsCompleted()
	{
		return (CompletedPieces() == 4);
	}
	int GetTeam() { return T->GetID(); }
};