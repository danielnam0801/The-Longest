#include<iostream>
#include "Core.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	if (!Core::GetInstance()->Init())
	{
		cout << "게임 초기화 실패!" << endl;
		Core::DestroyInstance();
		return 0;
	}

	Core::GetInstance()->Run();
	Core::DestroyInstance();
}