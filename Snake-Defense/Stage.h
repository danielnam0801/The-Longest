#pragma once
#include "define.h"
#include <string>

class Stage
{
public:
	Stage() = default;
	~Stage() = default;
private:
	char m_cStage[MAP_Y][MAP_X];
public:
	char GetBlock(int x, int y);
	void SetBlock(int x, int y, OBJECT_TYPE type);
public:
	bool Init(char* pFileName); // ������ �ҷ��ͼ� �ʱ�ȭ. 
	void Render();
};

