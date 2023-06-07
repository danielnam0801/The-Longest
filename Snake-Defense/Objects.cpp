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

SnakeBody::SnakeBody(bool isTail) : isTail(isTail)
{
	type = isTail ? OBJECT_TYPE::SNAKE_TAIL : OBJECT_TYPE::SNAKE_BODY;
}

void Snake::MoveNext()
{
	if (type == OBJECT_TYPE::SNAKE_HEAD) {
		
	}
	else {
		currentPos = front->beforePos;
	}

}
