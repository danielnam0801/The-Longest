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

void Snake::DieEffect()
{
    type = OBJECT_TYPE::SNAKE_DIE;
    Sleep(100);
    if (next != nullptr) {
        next->DieEffect();
        return; // 밑에 것을 실행시켜주지 않기 위함
    }
    // 마지막Effect까지 재생되었을때 처리
    Sleep(500); // 몇초 후 처리 할지
    SnakeManager::GetInst()->DieEvent();
}

void Snake::DestroyObject()
{

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
        beforeDir = currentDir;
        if (GetAsyncKeyState(VK_UP)) {
            if(currentDir.y != 1)
                currentDir = POINT{ 0, -1 };
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            if(currentDir.y != -1)
                currentDir = POINT{ 0, 1 };
        }
        if (GetAsyncKeyState(VK_RIGHT)) {
            if(currentDir.x != -1)
                currentDir = POINT{ 1, 0 };
        }
        if (GetAsyncKeyState(VK_LEFT)) {
            if(currentDir.x != 1)
                currentDir = POINT{ -1, 0 };
        } 
        currentPos = POINT{ currentPos.x + currentDir.x,
                            currentPos.y + currentDir.y};

        next->MoveNext();
        SnakeManager::GetInst()->CheckItem(currentPos);
        SnakeManager::GetInst()->CheckCrash(currentPos);
        SnakeManager::GetInst()->SetRotate(this); // 지금 객체를 넘겨줌
        SnakeManager::GetInst()->SetRender(currentPos, type);
        
        Sleep(140);
	}
	else if(type == OBJECT_TYPE::SNAKE_BODY) {
        beforePos = currentPos;
        beforeDir = currentDir;
        currentPos = front->beforePos;
        currentDir = front->beforeDir;
        next->MoveNext();
        SnakeManager::GetInst()->SetRender(currentPos, type);
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


