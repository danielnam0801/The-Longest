#include "SpawnManager.h"
#include "MapManager.h"
#include "Pos.h"
#include "define.h"

SpawnManager* SpawnManager::m_pInst = nullptr;
SpawnManager::SpawnManager() 
{

}

SpawnManager::~SpawnManager()
{
}

bool SpawnManager::Init()
{
	SAFE_DELETE(currentWall);
	return true;
}

void SpawnManager::Run()
{
	currentTime = time(NULL);
	SpawnWall();
	SpawnApple();
	WallControl(currentWall);
}

void SpawnManager::SpawnWall()
{
	if ((float)(currentTime - twallSpawnTime) > wallSpawnCool && currentWall == nullptr) {
		
		twallSpawnTime = time(NULL);
		MovingWall* movingWall = new MovingWall;
		
		int RandXORY = rand() % 2;
		int dir = rand() % 2;

		if (RandXORY == 0) { // RandomXPos

			int randXPos = RandomXPoint();
			if (dir == 0)	//아래에서 위쪽
			{ 
				movingWall->startSpawnPoint = Pos{ randXPos, MAP_Y - 1};
				movingWall->endSpawnPoint = Pos{ randXPos, 0 };
			}
			else //위쪽에서 아래
			{
				movingWall->startSpawnPoint = Pos{ randXPos, 0 };
				movingWall->endSpawnPoint = Pos{ randXPos, MAP_Y - 1};
			}
		}
		else 
		{
			int randYPos = RandomYPoint();

			if (dir == 0)	//왼쪽에서 오른쪽
			{
				movingWall->startSpawnPoint = Pos{ 0, randYPos };
				movingWall->endSpawnPoint = Pos{ MAP_X - 1, randYPos };
			}
			else    // 오른쪽에서 왼쪽
			{
				movingWall->startSpawnPoint = Pos{ MAP_X - 1, randYPos };
				movingWall->endSpawnPoint = Pos{ 0, randYPos };
			}	
		}

		movingWall->SpawnInit();
		currentWall = movingWall;
	}
}

void SpawnManager::SpawnApple()
{
	if ((float)(currentTime - tappleSpawnTime) > spawnAppleCool/3)
	{
	
		tappleSpawnTime = time(NULL);
		int randX = RandomXPoint();
		int randY = RandomYPoint();

		MapManager::GetInst()
			->GetStage()
			->SetBlock(randX, randY, OBJECT_TYPE::ITEM_APPLE);;
	}
}

void SpawnManager::WallControl(MovingWall* wall)
{
	if (wall == nullptr) return;
	
	if (wall->isEnd) {
		wall->EndEvent();
		currentWall = nullptr;
	}
	else wall->Moving();
}

int SpawnManager::RandomXPoint()
{
	return rand() % (MAP_X - 2) + 1;
}

int SpawnManager::RandomYPoint() {
	return rand() % (MAP_Y - 2) + 1;
}