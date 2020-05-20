#pragma once
class Position
{
public:
	int r, c;
	Position(int ri = 0, int ci = 0) :r(ri), c(ci) {}
	friend bool operator==(Position& A, Position& B)
	{
		return (A.r == B.r && A.c == B.c);
	}
};

