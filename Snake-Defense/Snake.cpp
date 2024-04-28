#include "pch.h"
#include "Snake.h"
#include "SnakeManager.h"
#include "Pos.h"

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
    if (next != nullptr)
        next->SetPosToBeforePos();
}

void Snake::CrashCheckThis(Pos pos)
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
    if (front == nullptr || 
        front == SnakeManager::GetInst()->snakeHead)
    {
        if (this == SnakeManager::GetInst()->snakeHead ||
            front == SnakeManager::GetInst()->snakeHead)
        {
            SnakeManager::GetInst()->snakeActive = false; // head가 죽었을 경우 아예 게임 종료
        }

        DieEffect();
        return;
    }
    else if (isCrash) { // 헤드가 아니고 충돌된 본인일경우

        front->type = OBJECT_TYPE::SNAKE_TAIL_DOWN; //내 앞에 아이를 꼬리로 만들어
        front->next = nullptr;
        
        SnakeManager::GetInst()->snakeTail = front;

        if (next != nullptr) {

            SnakeManager::GetInst()->
                SetRender(currentPos, OBJECT_TYPE::Blank);

            next->front = nullptr;//자기 바로 아래 자식의 본인과의 연결끊어줌 //필요없을수도 혹시 몰라서ㄴ
            next->DestroyThisAndChild();
            delete this;
        }
    }
    else { //충돌한애 자식들임
        SnakeManager::GetInst()->
            SetRender(currentPos, OBJECT_TYPE::Blank);

        if (next != nullptr)
        {
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

void Snake::Init(Pos pos, OBJECT_TYPE type)
{
    currentDir = Pos{ -1,0 };
    SetPos(pos.x, pos.y);
    SetType(type);
}

bool Snake::MoveNext()
{
    if (SnakeManager::GetInst()->snakeActive == false)
        return false;

    if (this == nullptr) 
        return false;

    if (front == nullptr) {
        beforePos = currentPos;
        beforeDir = currentDir;

        bool canInput = true;
        if (GetAsyncKeyState(VK_UP) && canInput)
        {
            canInput = false;
            if (currentDir.y != 1)
                currentDir = Pos{ 0, -1 };
        }
        if (GetAsyncKeyState(VK_DOWN) && canInput)
        {
            canInput = false;
            if (currentDir.y != -1)
                currentDir = Pos{ 0, 1 };
        }
        if (GetAsyncKeyState(VK_RIGHT) && canInput)
        {
            canInput = false;
            if (currentDir.x != -1)
                currentDir = Pos{ 1, 0 };
        }
        if (GetAsyncKeyState(VK_LEFT) && canInput)
        {
            canInput = false;
            if (currentDir.x != 1)
                currentDir = Pos{ -1, 0 };
        }

        currentPos = currentPos + currentDir;
        if (SnakeManager::GetInst()->CheckCrashHead(currentPos))
        {
            return false;
        }
        SnakeManager::GetInst()->CheckItem(currentPos);
        SnakeManager::GetInst()->SetRotate(this); // 지금 객체를 넘겨줌
        SnakeManager::GetInst()->SetRender(currentPos, type);
        
        if (!next->MoveNext()) 
            return false;
        else
            return true;
    }
    else if (type == OBJECT_TYPE::SNAKE_BODY) {
        beforePos = currentPos;
        beforeDir = currentDir;
        currentPos = front->beforePos;
        currentDir = front->beforeDir;

        SnakeManager::GetInst()->SetRender(currentPos, type);

        if (!next->MoveNext())
            return false;
        else
            return true;
    }
    else 
    {
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
    SnakeManager::GetInst()->AddLength();
    if (next == nullptr) return;
    next->ActiveCount();
}
