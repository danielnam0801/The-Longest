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
	cout << "�� ���� : " << length << endl;
	cout << "==========================================" << endl;
	cout << "�ٽ� �Ϸ��� y�� ��������!" << endl;
	cout << "������ �����Ϸ��� X�� ��������..." << endl;
	cout << "==========================================" << endl;
}
