#pragma once
#include "define.h"
class Snake {
public:
	bool isHead = false;
	OBJECT_TYPE type;
	POINT currentDir;
	POINT beforeDir;
	POINT currentPos;
	POINT beforePos;
	Snake* front;
	Snake* next;
public:
	void Init(POINT, OBJECT_TYPE);
	void MoveNext();
	void SetType(OBJECT_TYPE);
	void SetPos(int x, int y);
	void SetPosToBeforePos();
	void DieEffect();
};