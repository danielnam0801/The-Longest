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
	void MoveNext();
	void SetType(OBJECT_TYPE);
};

class SnakeHead : public Snake {
public:
	bool isCrash;
public:
	SnakeHead();
	void GetItem();
	void CrashCheck();

};
