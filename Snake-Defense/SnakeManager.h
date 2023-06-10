#pragma once
#include"define.h"
#include"Objects.h"

class SnakeManager {
private:
	static SnakeManager* m_pInst;
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
	void Run();
};