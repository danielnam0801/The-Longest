#pragma once
#include "Pos.h"

class MovingWall
{
public:
	bool canChangeDir = false;
	bool isEnd = false;
	int endCnt = 0;
	int timeCheck = 0;
	int movingCnt = 0;
	int callCnt = 0;
	Pos startSpawnPoint;
	Pos endSpawnPoint;
	Pos currentSpawnPoint;
	Pos targetPoint;
	Pos dir;
public:
	void SpawnInit();
	void ReverseDir();
	void Moving();
	void CollisionCheck();
	bool EndCheck();
	void EndEvent();
};

