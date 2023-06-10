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
	tail.front = snakeTail; // ������ ������ ���ο� ���� ������ ����
	tail.next = nullptr; // �����̱⿡ �������� �����
	tail.currentPos = tail.front->beforePos;

	snakeTail = &tail;
}

void SnakeManager::Run() {
	
}
