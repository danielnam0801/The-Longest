#include "Stage.h"
#include <fstream>
#include <iostream>
using namespace std;

Stage::Stage()
{

}

Stage::~Stage()
{

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
				std::cout << " ";
			}
			if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_UP){
				std::cout << "¡ã";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_DOWN){
				std::cout << "¡å";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_LEFT){
				std::cout << "¢¸";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_HEAD_RIGHT){
				std::cout << "¢º";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_BODY) {
				std::cout << "¡Þ";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_TAIL_DOWN) {
				std::cout << "¡ã";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_TAIL_UP){
				std::cout << "¡å";
			}
			else if (m_cStage[i][j] == (char)OBJECT_TYPE::SNAKE_TAIL_RIGHT){
				std::cout << "¢¸";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::SNAKE_TAIL_LEFT)) {
				std::cout << "¢º";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::ITEM_APPLE)) {
				std::cout << "¢¾";
			}
			else if (m_cStage[i][j] == (char)(OBJECT_TYPE::BG)) {
				std::cout << "¡á";
			}
			cout << " ";
		}
		cout << "\n";
	}
}
