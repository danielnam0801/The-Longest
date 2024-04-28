#pragma once
#include"define.h"
#include "console.h"
#include "MapManager.h"
#include "Stage.h"
#include "Core.h"
#include "Snake.h"
#include "Pos.h"

class SnakeManager : Manager {
private:
	static SnakeManager* m_pInst;
private:
	Stage * currentStage;
	int moveCnt = 0;
public:
	bool Init() override;
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
	void CreateSnakeParts();
	void SetRender(Pos pos, OBJECT_TYPE type);
	void SetRotate(Snake*);
	void CheckItem(Pos pos);
	bool CheckCrashHead(Pos pos);
	void FindCrashSnake(Pos pos);
	void DieEvent();
	void DeleteALL();
	void Run();
	void OneTimeRender();
public:
	void AddLength() { snakeLength++; }
	int GetLength();
};