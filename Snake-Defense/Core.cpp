#include <iostream>
#include "Core.h"
#include "console.h"
#include "MapManager.h"
#include "SnakeManager.h"
#include "SpawnManager.h"
#include "UI.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

using namespace std;
Core* Core::m_pInst = nullptr;
byte* m_pBuffer;

Core::Core() {

}

bool Core::Init()
{
	IsGameDone = false;
	if (MapManager::GetInst()->Init() == false)
		return false;
	if (SpawnManager::GetInst()->Init() == false)
		return false;	
	if (SnakeManager::GetInst()->Init() == false)
		return false;

	system("ShakeDefense");
	system("mode con cols=50 lines=30");
	SetCursor(false, 1);
	return true;
}

void Core::Run()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	byte* buff = new byte[100];

	UI* ui = new UI;

	int menuNum = ui->DrawMenu();
	system("cls");

	while (true) {
		if (menuNum >= 2) break;
		
		SpawnManager::GetInst()->Run();
		MapManager::GetInst()->Run(menuNum - 1);

		if (IsGameDone == true) {
			
			int maxLength = SnakeManager::GetInst()->GetLength();
			ui->DisplayDie(maxLength);

			if (ReGame()) {
				IsGameDone = false;
				Init();
			}
			else break;
		}
	}
}

bool Core::ReGame()
{
	char reset;
	cin >> reset;
	return reset == 'y';
}

