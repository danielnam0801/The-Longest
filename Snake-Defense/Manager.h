#pragma once
#include "define.h"
class Manager
{
protected:
	Manager(){};
	Manager(const Manager&) = delete;
	virtual bool Init() = 0;

public:
	//template <typename T>
	//static T* GetManager()
	//{
	//	return dynamic_cast<T>( m_pInst ); 
	//}
	//void DestroyInst() { SAFE_DELETE(m_pInst); }

//protected:
//	static Manager* m_pInst;
};