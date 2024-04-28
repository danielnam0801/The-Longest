#pragma once
#include "math.h"

typedef struct Pos
{
public:
	int x;
	int y;
public:
	float Length() 
	{
		return sqrtf(x * x + y * y);
	}

	void Normalize()
	{
		Pos Pos = { x,y };
		x /= Pos.Length();
		y /= Pos.Length();
		x *= -1;
		y *= -1;
	}

	Pos normalized()
	{
		Pos Pos = { x,y };
		const float& length = Pos.Length();
		Pos.x /= length;
		Pos.y /= length;
		Pos.x *= -1;
		Pos.y *= -1;
		return Pos;
	}
public:
	Pos operator*(const int& num)
	{
		Pos nPos;
		nPos.x = num * x;
		nPos.y = num * y;
		return nPos;
	}
	Pos operator+(const Pos& other)
	{
		Pos nPos;
		nPos.x = other.x + x;
		nPos.y = other.y + y;
		return nPos;
	}

	Pos operator-(const Pos& other)
	{
		Pos nPos;
		nPos.x = other.x - x;
		nPos.y = other.y - y;
		return nPos;
	}

	bool operator==(const Pos& other)
	{
		return other.x == x && other.y == y;
	}
};