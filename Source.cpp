#include "graphics.h"
#include <iostream>
#include"Dice.h"
#include"Ludo.h"
using namespace std;
int RowCol2Index(int r, int c)
{
	if (r == 0 && c == 0) return 0;
	if (r == 0) return c;
	if (c == 19) return 19 + r;
	if (r == 9) return 28 + (19 - c);
	if (c == 0) return 47 + (9 - r);
	cout << "ERROR IN ROWCOL2INDEX!!";
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
		r = Index - 19 ;
		c = 19;
	}
	else if (Index <= 47)
	{
		r = 9;
		c = 47-Index;
	}
	else if (Index <= 55)
	{
		r = 56-Index;
		c = 0;
	}
}
int main()
{
	Ludo L;
	L.Play();
	delay(10000000000);
}