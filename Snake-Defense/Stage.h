#pragma once
#include "define.h"
#include <string>
class Stage
{
public:
	Stage();
	~Stage();
private:
	char m_cStage[MAP_Y][MAP_X];
public:
	char GetBlock(int x, int y) { return m_cStage[y][x]; }
	void SetBlock(int x, int y, OBJECT_TYPE type);
public:
	bool Init(char* pFileName); // 초기화. -> 파일을 불러올거야. 
	void Render(); // 그 스테이지를 그리는거야. ㅇㅋ?
};

