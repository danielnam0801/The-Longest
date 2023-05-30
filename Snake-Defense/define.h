#pragma once
#include<Windows.h>

#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}
#define WIDTH 50
#define HEIGHT 50

enum class OBJECT_TYPE {
	SNAKE_HEAD = 1,
	SNAKE_BODY = 2,
	SNAKE_TAIL = 3,
	ITEM_APPLE = 4,
	BG = 5
};

