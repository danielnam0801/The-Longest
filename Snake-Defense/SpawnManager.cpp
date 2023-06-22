#include "SpawnManager.h"

SpawnManager* SpawnManager::m_pInst = nullptr;

SpawnManager::SpawnManager() {

}

SpawnManager::~SpawnManager()
{
}

bool SpawnManager::Init()
{
	return true;
}

void SpawnManager::Run()
{
	currentTime = time(NULL);
	SpawnWall();
	SpawnApple();
	//WallControl(walls);
}

void SpawnManager::SpawnWall()
{
	if ((float)(currentTime - twallSpawnTime) > wallSpawnCool) {
		twallSpawnTime = time(NULL);
		MovingWall movingWall;
		
		int RandXORY = rand() % 2;
		int dir = rand() % 2;
		if (RandXORY == 0) { // RandomXPos

			int randXPos = RandomXPoint();
			if (dir == 0) { //아래에서 위쪽

				movingWall.startSpawnPoint = POS{ randXPos, MAP_Y - 1};
				movingWall.endSpawnPoint = POS{ randXPos, 0 };
			}
			else{ // 위쪽에서 아래에서
				movingWall.startSpawnPoint = POS{ randXPos, 0 };
				movingWall.endSpawnPoint = POS{ randXPos, MAP_Y - 1};
			}
		}
		else {//Y
			int randYPos = RandomYPoint();
			if (dir == 0) { //왼쪽에서 오른쪽

				movingWall.startSpawnPoint = POS{ 0, randYPos };
				movingWall.endSpawnPoint = POS{ MAP_X - 1, randYPos };
			}
			else { // 오른쪽에서 왼쪽
				movingWall.startSpawnPoint = POS{ MAP_X - 1, randYPos };
				movingWall.endSpawnPoint = POS{ 0, randYPos };
			}
		}

		movingWall.SpawnInit();
		walls.push_back(movingWall);
	}
}

void SpawnManager::SpawnApple()
{
	if ((float)(currentTime - tappleSpawnTime) > spawnAppleCool) {
		tappleSpawnTime = time(NULL);
		int randX = RandomXPoint();
		int randY = RandomYPoint();

		MapManager::GetInst()->GetStage()->SetBlock(randX, randY, OBJECT_TYPE::ITEM_APPLE);;
	}
}

void SpawnManager::WallControl(std::vector<MovingWall>& walls)
{
	if (walls.size() == 0) return;

	std::vector<MovingWall>::iterator iter;
	for (iter = walls.begin(); iter != walls.end(); ) {
		if (iter->isEnd) {
			iter->EndEvent();
			iter = walls.erase(iter);
		}
		else {
			iter->MovingWall();
			iter++;
		}
	}
}

int SpawnManager::RandomXPoint()
{
	return rand() % (MAP_X - 2) + 1;
}

int SpawnManager::RandomYPoint() {
	return rand() % (MAP_Y - 2) + 1;
}