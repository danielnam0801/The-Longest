#include "Objects.h"
#include "SnakeManager.h"

void Snake::SetType(OBJECT_TYPE snakeType)
{
    type = snakeType;
}

void Snake::SetPos(int x, int y)
{
    currentPos.x = x;
    currentPos.y = y;
}

void Snake::SetPosToBeforePos()
{
    currentPos = beforePos;
    SnakeManager::GetInst()->SetRender(currentPos, type);
    SnakeManager::GetInst()->OneTimeRender();
    if(next != nullptr)
      next->SetPosToBeforePos();
}

void Snake::DieEffect()
{
    if (isHead) // Head일떄
    {
        int maxTwinkleCnt = 5;
        int currentTwinkleCnt = 0;
        while (currentTwinkleCnt <= maxTwinkleCnt) {
            Sleep(30);
            type = OBJECT_TYPE::SNAKE_DIE_HEAD;
            SnakeManager::GetInst()->SetRender(currentPos, type);
            SnakeManager::GetInst()->OneTimeRender();
            Sleep(30);
            type = OBJECT_TYPE::SNAKE_DIE;
            SnakeManager::GetInst()->SetRender(currentPos, type);
            SnakeManager::GetInst()->OneTimeRender();
            currentTwinkleCnt++;
        }
    }

    type = OBJECT_TYPE::SNAKE_DIE;
    SnakeManager::GetInst()->SetRender(currentPos, type);
    SnakeManager::GetInst()->OneTimeRender();
    Sleep(70);
    if (next != nullptr) { //꼬리일때
        next->DieEffect();
        return; // 밑에 것을 실행시켜주지 않기 위함
    }
    // 마지막Effect까지 재생되었을때 처리
    Sleep(500); // 몇초 후 처리 할지
    SnakeManager::GetInst()->DieEvent();
}

void Snake::Init(POS pos, OBJECT_TYPE type)
{
    currentDir = POS{ 0,0 };
    SetPos(pos.x, pos.y);
    SetType(type);
}

void Snake::MoveNext()
{
    if (SnakeManager::GetInst()->snakeActive == false) return;

	if (type == OBJECT_TYPE::SNAKE_HEAD_UP || type == OBJECT_TYPE::SNAKE_HEAD_DOWN ||
        type == OBJECT_TYPE::SNAKE_HEAD_LEFT || type == OBJECT_TYPE::SNAKE_HEAD_RIGHT) {
        beforePos = currentPos;
        beforeDir = currentDir;
        if (GetAsyncKeyState(VK_UP)) {
            if(currentDir.y != 1)
                currentDir = POS{ 0, -1 };
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            if(currentDir.y != -1)
                currentDir = POS{ 0, 1 };
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            if(currentDir.x != -1)
                currentDir = POS{ 1, 0 };
        }
        if (GetAsyncKeyState(VK_LEFT)) {
            if(currentDir.x != 1)
                currentDir = POS{ -1, 0 };
        } 
        currentPos = POS{ currentPos.x + currentDir.x,
                            currentPos.y + currentDir.y};

        SnakeManager::GetInst()->CheckItem(currentPos);
        SnakeManager::GetInst()->CheckCrash(currentPos);
        SnakeManager::GetInst()->SetRotate(this); // 지금 객체를 넘겨줌
        SnakeManager::GetInst()->SetRender(currentPos, type);
        
        next->MoveNext();
        Sleep(140);
	}
	else if(type == OBJECT_TYPE::SNAKE_BODY) {
        beforePos = currentPos;
        beforeDir = currentDir;
        currentPos = front->beforePos;
        currentDir = front->beforeDir;
        SnakeManager::GetInst()->SetRender(currentPos, type);
        
        next->MoveNext();
    }
    else {
        beforePos = currentPos;
        beforeDir = currentDir;
        currentPos = front->beforePos;
        currentDir = front->beforeDir;
        SnakeManager::GetInst()->SetRotate(this); // 지금 객체를 넘겨줌
        SnakeManager::GetInst()->SetRender(currentPos, type);
    }
    

    
}

void _movingWall::SpawnInit()
{
    isEnd = false;
    canChangeDir = false;
    currentSpawnPoint = startSpawnPoint;
    targetPoint = endSpawnPoint;
}

void _movingWall::ReverseDir()
{
    dir = dir * -1;
    targetPoint = startSpawnPoint;
}

void _movingWall::MovingWall()// 일단은 한칸씩 움직이기
{
    currentSpawnPoint = currentSpawnPoint + dir;
    if (EndCheck()) {
        endCnt++;
        if (endCnt == 2) isEnd = true;
       
        ReverseDir();//중간지점 도착
    }
}

bool _movingWall::EndCheck()
{
    return currentSpawnPoint.x == targetPoint.x 
        && currentSpawnPoint.y == targetPoint.y;
}

void _movingWall::EndEvent()
{
    delete this;
}

