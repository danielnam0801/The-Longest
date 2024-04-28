#pragma once
#include "define.h"
#include "Manager.h"

class Stage;
class MapManager : Manager
{
private:
	MapManager();
	~MapManager();
private:
	static MapManager* m_pInst;
public:
	static MapManager* GetInst()
	{
		if (m_pInst == nullptr)
		{
			m_pInst = new MapManager;
		}
		return m_pInst;
	}
	static void DestroyInst() { SAFE_DELETE(m_pInst); }
	// ���� ������ �־����.
private:
	Stage* m_pStage[STAGE_MAX_COUNT];
	int m_iCurStage;

public:
	Stage* GetStage() { return m_pStage[m_iCurStage]; }

public:
	void Run(int _iCurStage);
	bool Init() override;
	
};
