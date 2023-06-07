#include "Objects.h"

SNAKE::SnakeHead::SnakeHead()
{
	isCrash = false;
	type = OBJECT_TYPE::SNAKE_HEAD;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               

void SNAKE::SnakeHead::GetItem()
{

}

void SNAKE::SnakeHead::CrashCheck()
{
}

void SNAKE::Snake::SetType(OBJECT_TYPE snakeType)
{
    type = snakeType;
}

SNAKE::Snake::Snake()
{

}

void SNAKE::Snake::MoveNext()
{
	if (type == OBJECT_TYPE::SNAKE_HEAD) {
        beforePos = currentPos;
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            currentPos.y--;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            currentPos.y++;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            currentPos.x++;
            Sleep(100);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            currentPos.x--;
            Sleep(100);
        } 
        next->MoveNext();
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
