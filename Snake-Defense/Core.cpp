#include <iostream>
#include "Core.h"
#include "console.h"
#include "MapManager.h"
#include "SnakeManager.h"
#include "Objects.h"

using namespace std;
Core* Core::m_pInst = nullptr;

Core::Core() {

}

bool Core::Init()
{
	if (!MapManager::GetInst()->Init())
		return false;
	if (!SnakeManager::GetInst()->Init())
		return false;

	system("ShakeDefense");
	system("mode con cols=50 lines=50");
	Cursorset(false, 1);
	return true;
}

void Core::Run()
{
	int menuNum = MenuDraw();
	system("cls");
	while (true) {
		if (menuNum >= 2) break;
		MapManager::GetInst()->Run(menuNum - 1);
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
