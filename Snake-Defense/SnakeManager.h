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
public:
	bool Init();
	void CreateSnakeParts();
	void SetRender(POINT pos, OBJECT_TYPE type);
	void SetRotate(Snake*);
	void CheckItem(POINT pos);
	void CheckCrash(POINT pos);
	void DieEvent();
	void Run();
};