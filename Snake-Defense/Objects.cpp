#include "Objects.h"
#include "SnakeManager.h"
#include<math.h>
using namespace std::chrono;

POS Normalize(const POS& pos);
float Length(POS pos);
float easeOutSine(float x);
float easeInCirc(float x);

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

void Snake::CrashCheckThis(POS pos)
{
    if (currentPos == pos) 
    {
        isCrash = true;
        DestroyThisAndChild();
    }
    else {
        if (next == nullptr) return; //꼬리면 나가짐
        next->CrashCheckThis(pos); // 자식도 체크    
    }
}

void Snake::DestroyThisAndChild()
{
    if (front == nullptr || front == SnakeManager::GetInst()->snakeHead) {
        if (this == SnakeManager::GetInst()->snakeHead || front == SnakeManager::GetInst()->snakeHead)
            SnakeManager::GetInst()->snakeActive = false; // head가 죽었을 경우 아예 게임 종료
        
        DieEffect(); 
        return;
    }
    else if (isCrash) { // 헤드가 아니고 충돌된 본인일경우
        
        front->type = OBJECT_TYPE::SNAKE_TAIL_DOWN; //내 앞에 아이를 꼬리로 만들어
        front->next = nullptr;
        SnakeManager::GetInst()->snakeTail = front;

        if (next != nullptr) {

            SnakeManager::GetInst()->SetRender(currentPos, OBJECT_TYPE::Blank);
            
            next->front = nullptr;//자기 바로 아래 자식의 본인과의 연결끊어줌 //필요없을수도 혹시 몰라서ㄴ
            next->DestroyThisAndChild();
            delete this;
        }
    }
    else { //충돌한애 자식들임
        SnakeManager::GetInst()->SetRender(currentPos, OBJECT_TYPE::Blank);
                    
        if (next != nullptr) {
            next->DestroyThisAndChild();//남은 자식까지 지워줌
        }
        delete this;
    }
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
    currentDir = POS{ -1,0 };
    SetPos(pos.x, pos.y);
    SetType(type);
}

bool Snake::MoveNext()
{
    if (SnakeManager::GetInst()->snakeActive == false) return false;

    if (this == nullptr) return false;
	if (front == nullptr){
        beforePos = currentPos;
        beforeDir = currentDir;
        
        bool canInput = true;
        if (GetAsyncKeyState(VK_UP) && canInput) {
            canInput = false;
            if(currentDir.y != 1)
                currentDir = POS{ 0, -1 };
        }
        if (GetAsyncKeyState(VK_DOWN) && canInput) {
            canInput = false;
            if(currentDir.y != -1)
                currentDir = POS{ 0, 1 };
        }
        if (GetAsyncKeyState(VK_RIGHT) && canInput) {
            canInput = false;
            if(currentDir.x != -1)
                currentDir = POS{ 1, 0 };
        }
        if (GetAsyncKeyState(VK_LEFT) && canInput) {
            canInput = false;
            if(currentDir.x != 1)
                currentDir = POS{ -1, 0 };
        } 
        currentPos = POS{ currentPos.x + currentDir.x,
                            currentPos.y + currentDir.y};

        SnakeManager::GetInst()->CheckItem(currentPos);
        if (SnakeManager::GetInst()->CheckCrashHead(currentPos)) {
            return false;
        }
        SnakeManager::GetInst()->SetRotate(this); // 지금 객체를 넘겨줌
        SnakeManager::GetInst()->SetRender(currentPos, type);
        if (!next->MoveNext()) return false;
        else return true;
	}
	else if(type == OBJECT_TYPE::SNAKE_BODY) {
        beforePos = currentPos;
        beforeDir = currentDir;
        currentPos = front->beforePos;
        currentDir = front->beforeDir;
        
        SnakeManager::GetInst()->SetRender(currentPos, type);
        
        if (!next->MoveNext()) return false;
        else return true;
    }
    else {
        beforePos = currentPos;
        beforeDir = currentDir;
        currentPos = front->beforePos;
        currentDir = front->beforeDir;
        SnakeManager::GetInst()->SetRotate(this); // 지금 객체를 넘겨줌
        SnakeManager::GetInst()->SetRender(currentPos, type);
        return true;
    }
}

void Snake::ActiveCount()
{
    SnakeManager::GetInst()->snakeLength++;
    if (next == nullptr) return;
    next->ActiveCount();
}

void _movingWall::SpawnInit()
{
    isEnd = false;
    canChangeDir = false;
    timeCheck = 0;
    dir = Normalize(endSpawnPoint - startSpawnPoint);
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
    callCnt++;
    if (timeCheck > callCnt) return;
    
    callCnt = 0;
    movingCnt++;

    int time = 0;
    if(endCnt == 0)
        time = 3 / easeInCirc((float)movingCnt / (float)MAP_Y/2);
    else {
        time =  7 / easeInCirc((float)movingCnt / (float)MAP_Y/2);
    }
    timeCheck = time;

    currentSpawnPoint = currentSpawnPoint + dir;
    
    CollisionCheck();

    bool isTouch = false;
    if (EndCheck()) {
        endCnt++;
        isTouch = true;
        if (endCnt == 2) {
            isEnd = true;
            return;
        }
       
        ReverseDir();//중간지점 도착
    }

    if (endCnt == 0) {
        SnakeManager::GetInst()->SetRender(currentSpawnPoint, OBJECT_TYPE::Wall); //나중에 SetRender다른곳으로 옮겨야함
    }
    else {
        if (isTouch) {
            SnakeManager::GetInst()->SetRender(currentSpawnPoint, OBJECT_TYPE::BreakWall);
            movingCnt = 0;
            timeCheck = 100;
        }
        else
            SnakeManager::GetInst()->SetRender(currentSpawnPoint, OBJECT_TYPE::Blank);
    }
    
}

void _movingWall::CollisionCheck()
{
    char a = MapManager::GetInst()->GetStage()->GetBlock(currentSpawnPoint.x, currentSpawnPoint.y);
    //나중에 좀 더 깔끔하게 할 수 있는 방법을 찾아봐야함
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
        SnakeManager::GetInst()->FindCrashSnake(currentSpawnPoint);
    }
}

bool _movingWall::EndCheck()
{
    return currentSpawnPoint.x == targetPoint.x 
        && currentSpawnPoint.y == targetPoint.y;
}

void _movingWall::EndEvent()
{
    //delete this;
}

float Length(POS pos) {
    return sqrtf(pos.x * pos.x + pos.y * pos.y);
}
POS Normalize(const POS& pos)
{
    POS nPos = pos;
    nPos.x /= Length(pos);
    nPos.y /= Length(pos);
    nPos.x *= -1;
    nPos.y *= -1;
    return nPos;
}

const double PI = 3.1415926;
float easeOutSine(float x){
  
  return sin((x * PI) / 2);
}

float easeInCirc(float x){
    return x == 1 ? 1 : 1 - pow(2, -10 * x);
}