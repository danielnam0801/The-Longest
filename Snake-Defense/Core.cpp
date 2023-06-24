#include <iostream>
#include "Core.h"
#include "console.h"
#include "MapManager.h"
#include "SnakeManager.h"
#include "SpawnManager.h"
#include "Objects.h"

using namespace std;
Core* Core::m_pInst = nullptr;

Core::Core() {

}

bool Core::Init()
{
	IsGameDone = false;
	if (!MapManager::GetInst()->Init())
		return false;
	if (!SpawnManager::GetInst()->Init())
		return false;	
	if (!SnakeManager::GetInst()->Init())
		return false;

	system("ShakeDefense");
	system("mode con cols=50 lines=30");
	Cursorset(false, 1);
	return true;
}

void Core::Run()
{
	int menuNum = MenuDraw();
	system("cls");
	while (true) {
		if (menuNum >= 2) break;
		
		SpawnManager::GetInst()->Run();
		MapManager::GetInst()->Run(menuNum - 1);
		if (IsGameDone == true) {
			if (DieUI()) {
				IsGameDone = false;
				Init();
			}
			else break;
		}
	}
}


int Core::MenuDraw()
{
	cout << "1. Play" << endl;
	cout << "2. Exit" << endl;
	int iInput;
	cin >> iInput;
	return iInput;
}

bool Core::DieUI()
{
	cout << "뱀 길이 : " << SnakeManager::GetInst()->GetLength() << endl;
	cout << "==========================================" << endl;
	cout << "다시 하려면 y를 누르세요!" << endl;
	cout << "게임을 종료하려면 X를 누르세요..." << endl;
	cout << "==========================================" << endl;

	while (true) {
		if (_kbhit) {
			char ch;	
			ch = _getch();
			if (ch == 'x') return false;
			else if (ch == 'y') return true;
		}
	}

	return 0;
}


