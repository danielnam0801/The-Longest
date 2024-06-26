#include "Stage.h"
#include "console.h"
#include <fstream>
#include <iostream>
using namespace std;


char Stage::GetBlock(int x, int y)
{
	return m_cStage[y][x];
}

void Stage::SetBlock(int x, int y, OBJECT_TYPE type)
{
	m_cStage[y][x] = (char)type;
}

bool Stage::Init(char* pFileName)
{
	std::ifstream readfile;
	if (readfile.is_open())
		return false;
	readfile.open(pFileName);
	for (int i = 0; i < 20; i++)
	{
		readfile.getline(m_cStage[i], 21);
	}
	return true;
}

void Stage::Render()
{
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			if (m_cStage[i][j] == (char)OBJECT_TYPE::Blank){
				std::cout << "  ";
			}
			if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_UP){
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_DOWN){
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_LEFT){
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_RIGHT){
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_BODY) {
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_TAIL_DOWN) {
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_TAIL_UP){
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_TAIL_RIGHT){
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::SNAKE_TAIL_LEFT)) {
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::ITEM_APPLE)) {
				
				SetColor((int)COLOR::RED, (int)COLOR::BLACK);
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::Wall)) {
				//SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
				std::cout << "��";
			}else if (m_cStage[i][j] == (char)(OBJECT_TYPE::BreakWall)) {
				//SetColor((int)COLOR::BLACK, (int)COLOR::WHITE);
				std::cout << "��";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::SNAKE_DIE)) {\
				SetColor((int)COLOR::LIGHT_RED, (int)COLOR::BLACK);
				std::cout << "��";
			}else if (m_cStage[i][j] == (char)(OBJECT_TYPE::SNAKE_DIE_HEAD)) {\
				SetColor((int)COLOR::LIGHT_RED, (int)COLOR::BLACK);
				std::cout << "��";
			}

			SetColor((int)COLOR::WHITE, (int)COLOR::BLACK);
		}
		cout << "\n";
	}
}
