#pragma once
#include"define.h"
#include "console.h"
#include"Objects.h"
#include "MapManager.h"
#include "Stage.h"
#include "Core.h"

class SnakeManager {
private:
	static SnakeManager* m_pInst;
	Stage* currentStage;
	int moveCnt = 0;
public:
	static SnakeManager* GetInst()
	{
		if (m_pInst == nullptr)
		{
			m_pInst = new SnakeManager;
		}
		return m_pInst;
	}
	static void DestroyInst() { SAFE_DELETE(m_pInst); }
public:
	Snake* snakeHead;
	Snake* snakeTail;
	bool snakeActive;
	int snakeLength = 0;
public:
	bool Init();
	void CreateSnakeParts();
	void SetRender(POS pos, OBJECT_TYPE type);
	void SetRotate(Snake*);
	void CheckItem(POS pos);
	bool CheckCrashHead(POS pos);
	void FindCrashSnake(POS pos);
	void DieEvent();
	void DeleteALL();
	void Run();
	void OneTimeRender();
	int GetLength();
};