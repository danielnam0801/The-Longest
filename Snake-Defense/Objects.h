#pragma once
#include "define.h"
class Snake {
public:
	bool isHead = false;
	OBJECT_TYPE type;
	POS currentDir;
	POS beforeDir;
	POS currentPos;
	POS beforePos;
	Snake* front;
	Snake* next;
public:
	void Init(POS, OBJECT_TYPE);
	void MoveNext();
	void SetType(OBJECT_TYPE);
	void SetPos(int x, int y);
	void SetPosToBeforePos();
	void DieEffect();
};

typedef class _movingWall {
public:
	bool canChangeDir = false;
	bool isEnd = false;
	int endCnt = 0;
	POS startSpawnPoint;
	POS endSpawnPoint;
	POS currentSpawnPoint;
	POS targetPoint;
	POS dir;
public:
	void SpawnInit();
	void ReverseDir();
	void MovingWall();
	bool EndCheck();
	void EndEvent();
}MovingWall, *PMovingWall;
//POINT operator*(POINT point) { // 나중에 POS 클래스를 만든 후 operator연산을 적용가능하게 할꺼임
//	return POINT{point.x + }
//}