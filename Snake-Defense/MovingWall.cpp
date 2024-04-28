#include "MovingWall.h"
#include "Ease.h"
#include "chrono"
#include "SnakeManager.h"
#include "MapManager.h"
#include "define.h"
#include "Pos.h"

void MovingWall::SpawnInit()
{
    isEnd = false;
    canChangeDir = false;
    timeCheck = 0;

    dir = Pos{ endSpawnPoint - startSpawnPoint };
    dir.Normalize();

    currentSpawnPoint = startSpawnPoint;
    targetPoint = endSpawnPoint;
}

void MovingWall::ReverseDir()
{
    dir = dir * -1;
    targetPoint = startSpawnPoint;
}

void MovingWall::Moving()
{
    callCnt += 9;
    if (timeCheck > callCnt) return;

    callCnt = 0;
    movingCnt++;

    int time = 0;
    if (endCnt == 0)
    {
        time = 3 / easeInExpo((float)movingCnt / (float)MAP_Y / 2);
    }
    else 
    {
        time = 7 / easeInExpo((float)movingCnt / (float)MAP_Y / 2);
    }
    timeCheck = time;

    currentSpawnPoint = currentSpawnPoint + dir;

    CollisionCheck();

    bool isTouch = false;
    if (EndCheck())
    {
        endCnt++;
        isTouch = true;
        if (endCnt == 2)
        {
            isEnd = true;
            return;
        }

        ReverseDir();//중간지점 도착
    }

    if (endCnt == 0) {
        SnakeManager::GetInst()->SetRender(currentSpawnPoint, OBJECT_TYPE::Wall); //나중에 SetRender다른곳으로 옮겨야함
    }
    else 
    {
        if (isTouch) 
        {
            SnakeManager::GetInst()->SetRender(currentSpawnPoint, OBJECT_TYPE::BreakWall);
            movingCnt = 0;
            timeCheck = 100;
        }
        else
        {
            SnakeManager::GetInst()->SetRender(currentSpawnPoint, OBJECT_TYPE::Blank);
        }
    }

}

void MovingWall::CollisionCheck()
{
    char a = MapManager::GetInst()
        ->GetStage()
        ->GetBlock(currentSpawnPoint.x, currentSpawnPoint.y);
    
    if (a == (char)OBJECT_TYPE::SNAKE_BODY ||
        a == (char)OBJECT_TYPE::SNAKE_HEAD_DOWN ||
        a == (char)OBJECT_TYPE::SNAKE_HEAD_LEFT ||
        a == (char)OBJECT_TYPE::SNAKE_HEAD_RIGHT ||
        a == (char)OBJECT_TYPE::SNAKE_HEAD_UP ||
        a == (char)OBJECT_TYPE::SNAKE_TAIL_DOWN ||
        a == (char)OBJECT_TYPE::SNAKE_TAIL_LEFT ||
        a == (char)OBJECT_TYPE::SNAKE_TAIL_RIGHT ||
        a == (char)OBJECT_TYPE::SNAKE_TAIL_UP)
    {
        SnakeManager::GetInst()->
            FindCrashSnake(currentSpawnPoint);
    }
}

bool MovingWall::EndCheck()
{
    return currentSpawnPoint.x == targetPoint.x
        && currentSpawnPoint.y == targetPoint.y;
}

void MovingWall::EndEvent()
{
    delete this;
}
