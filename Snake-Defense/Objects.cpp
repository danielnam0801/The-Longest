#include "Objects.h"
#include "SnakeManager.h"

SnakeHead::SnakeHead()
{
	isCrash = false;
	type = OBJECT_TYPE::SNAKE_HEAD_UP;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

void SnakeHead::GetItem()
{

}

void SnakeHead::CrashCheck()
{
}

void Snake::SetType(OBJECT_TYPE snakeType)
{
    type = snakeType;
}

void Snake::SetPos(int x, int y)
{
    currentPos.x = x;
    currentPos.y = y;
}

void Snake::Init(POINT pos, OBJECT_TYPE type)
{
    SetPos(pos.x, pos.y);
    SetType(type);
}

void Snake::MoveNext()
{
	if (type == OBJECT_TYPE::SNAKE_HEAD_UP || type == OBJECT_TYPE::SNAKE_HEAD_DOWN ||
        type == OBJECT_TYPE::SNAKE_HEAD_LEFT || type == OBJECT_TYPE::SNAKE_HEAD_RIGHT) {
        beforePos = currentPos;

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            if(currentDir.y != 1)
                currentDir = POINT{ 0, -1 };
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            if(currentDir.y != -1)
                currentDir = POINT{ 0, 1 };
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if(currentDir.x != -1)
                currentDir = POINT{ 1, 0 };
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if(currentDir.x != 1)
                currentDir = POINT{ -1, 0 };
        } 
        currentPos = POINT{ currentPos.x + currentDir.x,
                            currentPos.y + currentDir.y};
        next->MoveNext();
        SnakeManager::GetInst()->CheckItem(currentPos);
        SnakeManager::GetInst()->SetRotate();
        SnakeManager::GetInst()->SetRender(currentPos, type);
        Sleep(150);
	}
	else if(type == OBJECT_TYPE::SNAKE_BODY) {
        beforePos = currentPos;
        currentPos = front->beforePos;
        next->MoveNext();
        SnakeManager::GetInst()->SetRender(currentPos, type);
    }
    else {
        beforePos = currentPos;
        currentPos = front->beforePos;
        SnakeManager::GetInst()->SetRender(currentPos, type);
    }
    

    
}


