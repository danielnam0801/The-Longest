#pragma once
#include "define.h"

class Core {
private:
	Core();
private:
	static Core* m_pInst;
public:
	static Core* GetInstance() {
		if (m_pInst == nullptr)
			m_pInst = new Core;
		return m_pInst;
	}
	static void DestroyInstance() {
		SAFE_DELETE(m_pInst);
	}
public:
	bool Init();
	void Run();
	int MenuDraw();
};