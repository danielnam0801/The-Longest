#include <iostream>
#include "Core.h"
#include "SnakeManager.h"
#include "Objects.h"

using namespace std;
Core* Core::m_pInst = nullptr;

Core::Core() {

}

bool Core::Init()
{
	if (!SnakeManager::GetInst()->Init())
		return false;

	system("ShakeDefense");
	system("mode con cols=100 lines=100");
	return true;
}

void Core::Run()
{
	int menuNum = MenuDraw();
	system("cls");
	while (true) {
		if (menuNum == 2) break;
		SnakeManager
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
