#include "SnakeManager.h"
SnakeManager* SnakeManager::m_pInst = nullptr;

bool SnakeManager::Init()
{	
	this->snakeHead = new SnakeHead;
	this->snakeHead->currentPos = POINT{ 50, 50 };
	this->snakeHead->type = OBJECT_TYPE::SNAKE_HEAD;
	return true;
}

void SnakeManager::CreateSnakeParts()
{
	Snake tail;
	tail.SetType(OBJECT_TYPE::SNAKE_TAIL);
	tail.front->SetType(OBJECT_TYPE::SNAKE_BODY);
	tail.front = snakeTail; // 기존의 꼬리를 새로운 꼬리 앞으로 설정
	tail.next = nullptr; // 꼬리이기에 다음것은 비워둠
	tail.currentPos = tail.front->beforePos;

	snakeTail = &tail;
}

void SnakeManager::Run() {
	
}
