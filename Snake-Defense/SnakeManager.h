#pragma once
#include"define.h"
#include"Objects.h"
#include "MapManager.h"
#include "Stage.h"

class SnakeManager {
private:
	static SnakeManager* m_pInst;
	Stage* currentStage;
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
public:
	bool Init();
	void CreateSnakeParts();
	void SetRender(POS pos, OBJECT_TYPE type);
	void SetRotate(Snake*);
	void CheckItem(POS pos);
	void CheckCrash(POS pos);
	void DieEvent();
	void DeleteALL();
	void OneTimeRender();
	void Run();
};