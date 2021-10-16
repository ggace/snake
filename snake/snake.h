#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <list>

using namespace std;

#include "common.h"

class Snake {
	typedef unsigned int SnakeLengthType;
public:
	Snake();
	void initialize();
	void set_direction(Keyboard key);
	void move();
	bool is_bitten();

	list<Position>& body();
	const list<Position> body() const;
	const Position head() const;
	const Position tail() const;

private:
	void move_up();
	void move_down();
	void move_left();
	void move_right();
	const int direction() const;

private:
	int direction_;
	list<Position> body_;
};

#endif // !__SNAKE_H__
