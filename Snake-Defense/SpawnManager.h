#pragma once
#include "define.h"
#include "MapManager.h"
#include "Objects.h"
#include "Stage.h"
#include <time.h>
#include <vector>

class SpawnManager {
private:
	SpawnManager();
	~SpawnManager();
private:
	static SpawnManager* m_pInst;
private:
	std::vector<MovingWall> walls;
public:
	static SpawnManager* GetInst()
	{
		if (m_pInst == nullptr)
		{
			m_pInst = new SpawnManager;
		}
		return m_pInst;
	}
	static void DestroyInst() { SAFE_DELETE(m_pInst); }
	// 맵을 가지고 있어야함.
public:
	POS currentSpawnPoint;
	time_t currentTime = time(NULL);
	time_t twallSpawnTime = time(NULL);
	time_t tappleSpawnTime = time(NULL);
	float wallSpawnCool = 5;
	float spawnAppleCool = 3;
public:
	bool Init();
	void Run();
	void SpawnWall();
	void SpawnApple();
	void WallControl(std::vector<MovingWall>& walls);
	int RandomXPoint();
	int RandomYPoint();
};