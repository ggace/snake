#include "snake.h"

//생성자
Snake::Snake() {
	initialize();
}

//head()
//뱀 머리 위치
const Position Snake::head() const {
	return body_.front();
}

//tail()
//뱀 꼬리 위치
const Position Snake::tail() const {
	return body_.back();
}

// body()
// ... 뱀 전체의 위치를 담고있는 list를 반환한다.
//
list<Position>& Snake::body()
{
	return body_;
}

// body()
// ... 뱀 전체의 위치를 담고있는 list를 상수객체로 반환한다.
//
const list<Position> Snake::body() const
{
	return body_;
}

//initialize()
//초기화
void Snake::initialize() {
	body_.clear();

	Position pos[2] = { {40, 12}, {40, 13} };
	body_.push_front(pos[0]);
	body_.push_back(pos[1]);

	direction_ = UP;
}

//set_direction()
//뱀의 움직이는 방향 설정
void Snake::set_direction(Keyboard key) {
	if (direction_ == UP && key == DOWN) return;
	if (direction_ == DOWN && key == UP) return;
	if (direction_ == LEFT && key == RIGHT) return;
	if (direction_ == RIGHT && key == LEFT) return;

	direction_ = key;
}

//move()
// ... 기존의 머리는 몸통으로 바꾸어 출력하고
// ... 진행방향에 따라 알맞는 move함수를 호출한다.
void Snake::move() {
	putchar_at_xy(head().X, head().Y, 'o');

	switch (direction_) {
	case UP:	move_up();		break;
	case DOWN:	move_down();	break;
	case LEFT:	move_left();	break;
	case RIGHT:	move_right();	break;
	}
}

//move_up()
void Snake::move_up() {
	Position new_head = { head().X, head().Y - 1 };
	body_.push_front(new_head);
}
//move_down()
void Snake::move_down() {
	Position new_head = { head().X, head().Y + 1 };
	body_.push_front(new_head);
}
//move_left()
void Snake::move_left() {
	Position new_head = { head().X - 1 , head().Y };
	body_.push_front(new_head);
}
//move_right()
void Snake::move_right() {
	Position new_head = { head().X + 1, head().Y };
	body_.push_front(new_head);
}

//is_bitten()
// ... 뱀이 자기 몸을 물었으면 true, 아니면 false를 반환한다.
bool Snake::is_bitten() {
	list<Position>::const_iterator iter = body_.begin();
	while (++iter != body_.end()) {
		if ((iter->X == head().X) && (iter->Y == head().Y)) {
			return true;
		}
	}

	return false;
}

