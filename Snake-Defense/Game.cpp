#include<iostream>
#include "Core.h"

using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	if (!Core::GetInstance()->Init())
	{
		cout << "���� �ʱ�ȭ ����!" << endl;
		Core::DestroyInstance();
		return 0;
	}

	Core::GetInstance()->Run();
	Core::DestroyInstance();
}