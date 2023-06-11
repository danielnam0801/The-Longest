#include "SnakeManager.h"
#include <conio.h>
SnakeManager* SnakeManager::m_pInst = nullptr;

bool SnakeManager::Init()
{	
	if (MapManager::GetInst() == nullptr) return false;
	currentStage = MapManager::GetInst()->GetStage();
	
	this->snakeHead = new SnakeHead;
	POINT headStartPoint = POINT{10,10};
	snakeHead->Init(headStartPoint, OBJECT_TYPE::SNAKE_HEAD_UP);

	this->snakeTail = new Snake;
	POINT tailStartPoint = POINT{11,10};
	snakeTail->Init(tailStartPoint, OBJECT_TYPE::SNAKE_TAIL_UP);

	this->snakeHead->next = snakeTail;
	this->snakeTail->front = snakeHead;
	return true;
}

void SnakeManager::CreateSnakeParts()
{
	Snake* tail = new Snake;
	snakeTail->next = tail;
	snakeTail->SetType(OBJECT_TYPE::SNAKE_BODY);
	tail->front = snakeTail;

	snakeTail = tail;
 
	tail->currentPos = tail->front->beforePos;
	tail->beforePos = tail->currentPos;
	tail->next = nullptr; // 꼬리이기에 다음것은 비워둠
}

void SnakeManager::CheckItem(POINT pos)
{
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::ITEM_APPLE) {
		CreateSnakeParts();
	}
}

void SnakeManager::SetRender(POINT pos, OBJECT_TYPE type)
{
	currentStage->SetBlock(pos.x, pos.y, type);
}

void SnakeManager::SetRotate()
{
	if (snakeHead->currentDir.x == 0) {
		if (snakeHead->currentDir.y == -1) {
			snakeHead->SetType(OBJECT_TYPE::SNAKE_HEAD_UP);
			snakeTail->SetType(OBJECT_TYPE::SNAKE_TAIL_UP);
		}
		if (snakeHead->currentDir.y == 1) {
			snakeHead->SetType(OBJECT_TYPE::SNAKE_HEAD_DOWN);
			snakeTail->SetType(OBJECT_TYPE::SNAKE_TAIL_DOWN);
		}
	}
	else {
		if (snakeHead->currentDir.x == -1) {
			snakeHead->SetType(OBJECT_TYPE::SNAKE_HEAD_LEFT);
			snakeTail->SetType(OBJECT_TYPE::SNAKE_TAIL_LEFT);
		}
		if (snakeHead->currentDir.x == 1) {
			snakeHead->SetType(OBJECT_TYPE::SNAKE_HEAD_RIGHT);
			snakeTail->SetType(OBJECT_TYPE::SNAKE_TAIL_RIGHT);
		}
	}
}

void SnakeManager::Run() {

	snakeHead->MoveNext();
	SetRender(snakeTail->beforePos, OBJECT_TYPE::Blank);
}
