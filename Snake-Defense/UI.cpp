#include "UI.h"
#include <iostream>
using namespace std;

int UI::DrawMenu()
{
	cout << "1. Play" << endl;
	cout << "2. Exit" << endl;
	int iInput;
	cin >> iInput;
	return iInput;
}

void UI::DisplayDie(int length)
{
	cout << "뱀 길이 : " << length << endl;
	cout << "==========================================" << endl;
	cout << "다시 하려면 y를 누르세요!" << endl;
	cout << "게임을 종료하려면 X를 누르세요..." << endl;
	cout << "==========================================" << endl;
}
