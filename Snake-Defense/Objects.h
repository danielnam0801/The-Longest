#pragma once
#include "define.h"
class Snake {
public:
	OBJECT_TYPE type;
	POINT currentPos;
	POINT beforePos;
	Snake* front;
	void MoveNext();
};

class SnakeHead : public Snake {
public:
	bool isCrash;
public: 
	SnakeHead();
	void GetItem();
	void CrashCheck();
};

class SnakeBody : public Snake{
private:
	bool isTail;
public:
	SnakeBody(bool isTail);
};