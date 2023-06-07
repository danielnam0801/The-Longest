#pragma once
#include "define.h"
namespace SNAKE {
	class Snake {
	public:
		Snake();
		OBJECT_TYPE type;
		POINT currentPos;
		POINT beforePos;
		Snake* front;
		Snake* next;
		void MoveNext();
		void SetType(OBJECT_TYPE);
	};

	class SnakeHead : public Snake {
	public:
		bool isCrash;
	public: 
		SnakeHead();
		void GetItem();
		void CrashCheck();
	};
}