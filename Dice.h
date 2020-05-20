#pragma once
#include<iostream>
using namespace std;
class Dice
{
public:
	int Ds[3];
	int size;
	void UpdateDiceValues(int r, int c);
	void RollDice(int r,int c, bool Try = false);
	void PrintDiceAt(int ri, int ci);
	bool IsEmpty() { return size == 0; }
	bool HasSix()
	{
		for (int i = 0; i < size; i++)
		{
			if (Ds[i] == 6)
				return true;
		}
		return false;
	}
	void RemoveNum(int N)
	{
		for (int i = 0; i < size; i++)
		{
			if (Ds[i] == N)
			{
				swap(Ds[i], Ds[size - 1]);
				Ds[size - 1] = 0;
				size--;
				return;
			}
		}
		cout << "\nERROR IN REMOVENUM OF DICE!!!\n";
	}
};
