#include "Objects.h"

SnakeHead::SnakeHead()
{
	isCrash = false;
	type = OBJECT_TYPE::SNAKE_HEAD;
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

void Snake::MoveNext()
{
	if (type == OBJECT_TYPE::SNAKE_HEAD) {
        beforePos = currentPos;
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            currentDir = POINT{ 0, -1 };
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            currentDir = POINT{ 0, 1 };
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            currentDir = POINT{ 1, 0 };
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            currentDir = POINT{ -1, 0 };
        } 
        currentPos = POINT{ currentPos.x + currentDir.x,
                            currentPos.y + currentDir.y};
        next->MoveNext();
        Sleep(1000);
	}
	else if(type == OBJECT_TYPE::SNAKE_BODY) {
        beforePos = currentPos;
        currentPos = front->beforePos;
        next->MoveNext();
    }
    else {
        beforePos = currentPos;
        currentPos = front->beforePos;
    }

}


