#include "SnakeManager.h"
#include <conio.h>
SnakeManager* SnakeManager::m_pInst = nullptr;

bool SnakeManager::Init()
{	
	if (MapManager::GetInst() == nullptr) return false;
	
	snakeActive = true;
	currentStage = MapManager::GetInst()->GetStage();
	
	this->snakeHead = new Snake;
	snakeHead->isHead = true;
	POINT headStartPoint = POINT{10,10};
	snakeHead->Init(headStartPoint, OBJECT_TYPE::SNAKE_HEAD_UP);

	this->snakeTail = new Snake;
	POINT tailStartPoint = POINT{11,10};
	snakeTail->Init(tailStartPoint, OBJECT_TYPE::SNAKE_TAIL_UP);
	snakeTail->next = nullptr;

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

void SnakeManager::SetRender(POINT pos, OBJECT_TYPE type)
{
	currentStage->SetBlock(pos.x, pos.y, type);
}

void SnakeManager::SetRotate(Snake* currentSnake)
{
	if (currentSnake == snakeHead) {
		if (currentSnake->currentDir.x == 0) {
			if (currentSnake->currentDir.y == -1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_HEAD_UP);
			if (currentSnake->currentDir.y == 1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_HEAD_DOWN);
		}
		else {
			if (currentSnake->currentDir.x == -1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_HEAD_LEFT);
			if (currentSnake->currentDir.x == 1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_HEAD_RIGHT);
		}
	}
	else if(currentSnake == snakeTail) { //꼬리
		if (currentSnake->currentDir.x == 0) {
			if (currentSnake->currentDir.y == -1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_TAIL_UP);
			if (currentSnake->currentDir.y == 1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_TAIL_DOWN);
		}
		else {
			if (currentSnake->currentDir.x == -1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_TAIL_LEFT);
			if (currentSnake->currentDir.x == 1)
				currentSnake->SetType(OBJECT_TYPE::SNAKE_TAIL_RIGHT);
		}
	}
	else { // 꼬리나 머리가 아닌 객체가 들어옴
		return;
	}
}

void SnakeManager::CheckItem(POINT pos)
{
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::ITEM_APPLE) {
		CreateSnakeParts();
		//sound플레이등..
	}
}

void SnakeManager::CheckCrash(POINT pos)
{
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::Wall) {
		
		//게임 종료
		snakeActive = false;
		SetRender(snakeHead->currentPos, OBJECT_TYPE::BreakWall);
		OneTimeRender();

		//shakeHead만 한칸 미루기
		snakeHead->currentPos = snakeHead->beforePos;
		snakeHead->beforePos = snakeHead->next->currentPos;
		SnakeManager::GetInst()->SetRender(snakeHead->currentPos, OBJECT_TYPE::Blank);

		snakeHead->SetPosToBeforePos();
		snakeHead->DieEffect();
	}
}

void SnakeManager::DieEvent()
{
	Sleep(10000);
}

void SnakeManager::DeleteALL()
{
	while (snakeHead != NULL) {
		Snake* delTemp = snakeHead;
		snakeHead = delTemp->next;
		delete delTemp;
	}
}

void SnakeManager::OneTimeRender()
{
	system("cls");
	currentStage->Render();
}

void SnakeManager::Run() {

	snakeHead->MoveNext();
	SetRender(snakeTail->beforePos, OBJECT_TYPE::Blank);
}
