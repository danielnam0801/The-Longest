#pragma once
#include<Windows.h>

#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}
#define MAP_Y 20
#define MAP_X 20
#define STAGE_MAX_COUNT 1

enum class OBJECT_TYPE {
	Blank = '0',
	SNAKE_HEAD_UP = '1',
	SNAKE_HEAD_DOWN ='2',
	SNAKE_HEAD_LEFT = '3',
	SNAKE_HEAD_RIGHT = '4',
	SNAKE_BODY = '5',
	SNAKE_TAIL_UP = '6',
	SNAKE_TAIL_DOWN = '7',
	SNAKE_TAIL_LEFT ='8',
	SNAKE_TAIL_RIGHT = '9',
	ITEM_APPLE = '*',
	BG = '#',
};

