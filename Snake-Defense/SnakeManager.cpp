#include "SnakeManager.h"
#include <conio.h>
SnakeManager* SnakeManager::m_pInst = nullptr;

bool SnakeManager::Init()
{	
	if (MapManager::GetInst() == nullptr) return false;
	
	snakeActive = true;
	currentStage = MapManager::GetInst()->GetStage();
	
	this->snakeHead = new Snake;
	POS headStartPoint = POS{10,10};
	snakeHead->Init(headStartPoint, OBJECT_TYPE::SNAKE_HEAD_UP);
	snakeHead->isHead = true;
	snakeHead->front = nullptr;

	this->snakeTail = new Snake;
	POS tailStartPoint = POS{11,10};
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
	tail->next = nullptr; // �����̱⿡ �������� �����
}

void SnakeManager::SetRender(POS pos, OBJECT_TYPE type)
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
	else if(currentSnake == snakeTail) { //����
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
	else { // ������ �Ӹ��� �ƴ� ��ü�� ����
		return;
	}
}

void SnakeManager::CheckItem(POS pos)
{
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::ITEM_APPLE ||
		currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::SNAKE_DIE) {
		CreateSnakeParts();
		//sound�÷��̵�..
	}
}

bool SnakeManager::CheckCrashHead(POS pos)
{
	//���߿� ��Ʈ�������� �ٲ������
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::Wall ||
		currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::BreakWall ||
		currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::SNAKE_BODY)
	{
		//���� ����
		snakeActive = false;
		SetRender(snakeHead->currentPos, OBJECT_TYPE::BreakWall);
		OneTimeRender();

		//shakeHead�� ��ĭ �̷��
		snakeHead->currentPos = snakeHead->beforePos;
		snakeHead->beforePos = snakeHead->next->currentPos;
		SnakeManager::GetInst()->SetRender(snakeHead->currentPos, OBJECT_TYPE::Blank);

		snakeHead->SetPosToBeforePos();
		snakeHead->DieEffect();

		return true;
	}
	return false;
}


void SnakeManager::FindCrashSnake(POS pos)
{
	snakeHead->CrashCheckThis(pos);
}

void SnakeManager::DieEvent()
{
	if (snakeActive == false) { //��¥ ������
		Gotoxy(0, 0);
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
	Gotoxy(0, 0);
	currentStage->Render();
}

int SnakeManager::GetLength()
{
	snakeLength = 0;
	snakeHead->ActiveCount();
	return snakeLength;
}


void SnakeManager::Run() {
	moveCnt++;
	if (moveCnt < 17) return;
	moveCnt = 0;
	if(!snakeHead->MoveNext()) return;
	SetRender(snakeTail->beforePos, OBJECT_TYPE::Blank);
}
