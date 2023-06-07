#include "Objects.h"
#include <vector>
using namespace std;
using namespace SNAKE;

class SnakeManager {
public:
	Snake* SnakeHead;
	Snake* SnakeTail;
public:
	void Init() {
		SnakeHead = new SNAKE::SnakeHead();
	}
	void CreateSnakeParts() {
		Snake tail;
		tail.SetType(OBJECT_TYPE::SNAKE_TAIL);
		tail.front->SetType(OBJECT_TYPE::SNAKE_BODY);
		tail.front = SnakeTail; // 기존의 꼬리를 새로운 꼬리 앞으로 설정
		tail.next = nullptr; // 꼬리이기에 다음것은 비워둠
		tail.currentPos = tail.front->beforePos;
		
		SnakeTail = &tail;
	}
};