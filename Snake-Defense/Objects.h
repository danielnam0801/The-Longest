#pragma once
#include "define.h"
class Snake {
public:
	OBJECT_TYPE type;
	POINT currentPos;
	POINT beforePos;
	Snake* next;
};

class SnakeHead : public Snake {
public:
	bool isCrash;
public: 
	SnakeHead();
	void GetItem();
	void Move();
};

class SnakeBody : public Snake{
private:
	bool isTail;
public:
	SnakeBody();
	void SetPOS(int x, int y);

};