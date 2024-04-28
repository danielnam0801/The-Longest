#include "SnakeManager.h"
#include "MapManager.h"
#include "Pos.h"
#include <conio.h>

SnakeManager* SnakeManager::m_pInst = nullptr;
bool SnakeManager::Init()
{	
	snakeActive = true;
	currentStage = MapManager::GetInst()->GetStage();
	
	this->snakeHead = new Snake;
	Pos headStartPoint = Pos{10,10};
	snakeHead->Init(headStartPoint, OBJECT_TYPE::SNAKE_HEAD_UP);
	snakeHead->isHead = true;
	snakeHead->front = nullptr;

	this->snakeTail = new Snake;
	Pos tailStartPoint = Pos{11,10};
	snakeTail->Init(tailStartPoint, OBJECT_TYPE::SNAKE_TAIL_UP);
	snakeTail->next = nullptr;
	snakeTail->front = snakeHead;

	this->snakeHead->next = snakeTail;
	snakeHead->MoveNext();

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

void SnakeManager::SetRender(Pos pos, OBJECT_TYPE type)
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

void SnakeManager::CheckItem(Pos pos)
{
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::ITEM_APPLE ||
		currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::SNAKE_DIE) {
		CreateSnakeParts();
		//sound플레이등..
	}
}

bool SnakeManager::CheckCrashHead(Pos pos)
{
	//나중에 비트연산으로 바꿔줘야함
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::Wall ||
		currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::BreakWall ||
		currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::SNAKE_BODY)
	{
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

		return true;
	}
	return false;
}


void SnakeManager::FindCrashSnake(Pos pos)
{
	snakeHead->CrashCheckThis(pos);
}

void SnakeManager::DieEvent()
{
	if (snakeActive == false) { //진짜 죽은거
		SetCursorPosition(0, 0);
		Core::GetInstance()->IsGameDone = true;
	}
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
	SetCursorPosition(0, 0);
	currentStage->Render();
}

int SnakeManager::GetLength()
{
	snakeLength = 0;
	snakeHead->ActiveCount();
	return snakeLength;
}


void SnakeManager::Run() {
	moveCnt+= 9;
	if (moveCnt < 17) return;
	moveCnt = 0;
	if(!snakeHead->MoveNext()) return;
	SetRender(snakeTail->beforePos, OBJECT_TYPE::Blank);
}
