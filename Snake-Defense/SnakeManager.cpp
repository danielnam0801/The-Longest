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
	POS headStartPoint = POS{10,10};
	snakeHead->Init(headStartPoint, OBJECT_TYPE::SNAKE_HEAD_UP);

	this->snakeTail = new Snake;
	POS tailStartPoint = POS{11,10};
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
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::ITEM_APPLE) {
		CreateSnakeParts();
		//sound�÷��̵�..
	}
}

void SnakeManager::CheckCrash(POS pos)
{
	//���߿� ��Ʈ�������� �ٲ������
	if (currentStage->GetBlock(pos.x, pos.y) == (char)OBJECT_TYPE::Wall ||
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
