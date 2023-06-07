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
		tail.front = SnakeTail; // ������ ������ ���ο� ���� ������ ����
		tail.next = nullptr; // �����̱⿡ �������� �����
		tail.currentPos = tail.front->beforePos;
		
		SnakeTail = &tail;
	}
};