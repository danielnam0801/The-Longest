#include<iostream>
#include "Core.h"

using namespace std;

int main() {
	if (!Core::GetInstance()->Init())
	{
		cout << "���� �ʱ�ȭ ����!" << endl;
		Core::DestroyInstance();
		return 0;
	}
	Core::GetInstance()->Run();
	Core::DestroyInstance();
}