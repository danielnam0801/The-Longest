#include "SpawnManager.h"

SpawnManager* SpawnManager::m_pInst = nullptr;

SpawnManager::SpawnManager() {

}

SpawnManager::~SpawnManager()
{
}

bool SpawnManager::Init()
{
	if (currentWall != nullptr)
		delete currentWall;
	currentWall = nullptr;
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
			if (dir == 0) { //�Ʒ����� ����

				movingWall->startSpawnPoint = POS{ randXPos, MAP_Y - 1};
				movingWall->endSpawnPoint = POS{ randXPos, 0 };
			}
			else{ // ���ʿ��� �Ʒ�����
				movingWall->startSpawnPoint = POS{ randXPos, 0 };
				movingWall->endSpawnPoint = POS{ randXPos, MAP_Y - 1};
			}
		}
		else {//Y
			int randYPos = RandomYPoint();
			if (dir == 0) { //���ʿ��� ������

				movingWall->startSpawnPoint = POS{ 0, randYPos };
				movingWall->endSpawnPoint = POS{ MAP_X - 1, randYPos };
			}
			else { // �����ʿ��� ����
				movingWall->startSpawnPoint = POS{ MAP_X - 1, randYPos };
				movingWall->endSpawnPoint = POS{ 0, randYPos };
			}
		}

		movingWall->SpawnInit();
		currentWall = movingWall;
		//walls.push_back(movingWall);
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

void SpawnManager::WallControl(MovingWall* wall)
{
	if (wall == nullptr) return;
	
	if (wall->isEnd) {
		wall->EndEvent();
		currentWall = nullptr;
	}
	else wall->MovingWall();
}

int SpawnManager::RandomXPoint()
{
	return rand() % (MAP_X - 2) + 1;
}

int SpawnManager::RandomYPoint() {
	return rand() % (MAP_Y - 2) + 1;
}