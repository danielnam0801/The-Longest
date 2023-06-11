#pragma once
#include "define.h"
class Snake {
public:
	OBJECT_TYPE type;
	POINT currentDir;
	POINT currentPos;
	POINT beforePos;
	Snake* front;
	Snake* next;
public:
	void Init(POINT, OBJECT_TYPE);
	void MoveNext();
	void SetType(OBJECT_TYPE);
	void SetPos(int x, int y);
};

class SnakeHead : public Snake {
public:
	bool isCrash;
public:
	SnakeHead();
	void GetItem();
	void CrashCheck();

};
