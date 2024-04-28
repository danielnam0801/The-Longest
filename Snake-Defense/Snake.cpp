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
        if (next == nullptr) return; //������ ������
        next->CrashCheckThis(pos); // �ڽĵ� üũ    
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
            SnakeManager::GetInst()->snakeActive = false; // head�� �׾��� ��� �ƿ� ���� ����
        }

        DieEffect();
        return;
    }
    else if (isCrash) { // ��尡 �ƴϰ� �浹�� �����ϰ��

        front->type = OBJECT_TYPE::SNAKE_TAIL_DOWN; //�� �տ� ���̸� ������ �����
        front->next = nullptr;
        
        SnakeManager::GetInst()->snakeTail = front;

        if (next != nullptr) {

            SnakeManager::GetInst()->
                SetRender(currentPos, OBJECT_TYPE::Blank);

            next->front = nullptr;//�ڱ� �ٷ� �Ʒ� �ڽ��� ���ΰ��� ��������� //�ʿ�������� Ȥ�� ���󼭤�
            next->DestroyThisAndChild();
            delete this;
        }
    }
    else { //�浹�Ѿ� �ڽĵ���
        SnakeManager::GetInst()->
            SetRender(currentPos, OBJECT_TYPE::Blank);

        if (next != nullptr)
        {
            next->DestroyThisAndChild();//���� �ڽı��� ������
        }
        delete this;
    }
}

void Snake::DieEffect()
{
    if (isHead) // Head�ϋ�
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
    if (next != nullptr) { //�����϶�
        next->DieEffect();
        return; // �ؿ� ���� ����������� �ʱ� ����
    }
    // ������Effect���� ����Ǿ����� ó��
    Sleep(500); // ���� �� ó�� ����
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
        SnakeManager::GetInst()->SetRotate(this); // ���� ��ü�� �Ѱ���
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
        SnakeManager::GetInst()->SetRotate(this); // ���� ��ü�� �Ѱ���
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
