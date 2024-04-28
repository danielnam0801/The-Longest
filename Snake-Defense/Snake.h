#pragma once
#include "Pos.h"

class Snake
{
public:
	bool isHead = false;
	bool isCrash = false;
	OBJECT_TYPE type;
	Pos currentDir;
	Pos beforeDir;
	Pos currentPos;
	Pos beforePos;
	Snake* front;
	Snake* next;
public:
	void Init(Pos, OBJECT_TYPE);
	bool MoveNext();
	void ActiveCount();
	void SetType(OBJECT_TYPE);
	void SetPos(int x, int y);
	void SetPosToBeforePos();
	void CrashCheckThis(Pos);
	void DestroyThisAndChild();
	void DieEffect();
};

