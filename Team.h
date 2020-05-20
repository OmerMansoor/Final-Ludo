#pragma once
#include<string>
using namespace std;
class Player;
class Team
{
public:
	int ID;
	Player* Ps;
	int NOP;
	int GetID() { return ID; }
	Team(int id, int Nop, Player* ps) :ID(id), NOP(Nop), Ps(ps) {}
	Team() {}
	void InitTeam(int id, int Nop, Player* ps)
	{
		ID = id;
		NOP = Nop;
		Ps = ps;
	}
	friend bool operator==(const Team &A, const Team &B)
	{
		return (A.ID == B.ID);
	}
	/*bool IsCompleted()
	{
		for (int i = 0; i < NOP; i++)
		{
			if (!Ps[i].IsCompleted()) return false;
		}
		return true;
	}*/
};

