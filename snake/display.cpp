#include <iostream>
#include <cstdlib>
#include "display.h"

//생성자
Display::Display() : max_x_(79), max_y_(24) {}

//max_x()
const int Display::max_x() const {
	return max_x_;
}

//max_y()
const int Display::max_y() const {
	return max_y_;
}

//print_prompt()
//메세지 출력
void Display::print_prompt(const char* msg) {
	go_to_xy(0, 10);
	for (int i = 0; i < 80; i++) {
		printf("-");
	}	
	go_to_xy(0, 12);
	for (int i = 0; i < 80; i++) {
		printf("-");
	}

	go_to_xy(40 - strlen(msg) / 2, 11);
	printf("%s", msg);
}

//print_wall()
// ... 뱀이 벗어날 수 없는 범위인 벽을 출력한다.
void Display::print_wall() {
	putchar_at_xy(0, 0, '+');
	putchar_at_xy(max_x(), 0, '+');
	putchar_at_xy(0, max_y(), '+');
	putchar_at_xy(max_x(), max_y(), '+');

	// 상단 가로줄을 출력한다.
	for (int x = 1, y = 0; x < max_x(); x++)
		putchar_at_xy(x, y, '-');

	// 하단 가로줄을 출력한다.
	for (int x = 1, y = max_y(); x < max_x(); x++)
		putchar_at_xy(x, y, '-');

	// 좌측 세로줄을 출력한다.
	for (int x = 0, y = 1; y < max_y(); y++)
		putchar_at_xy(x, y, '|');

	// 우측 세로줄을 출력한다.
	for (int x = max_x(), y = 1; y < max_y(); y++)
		putchar_at_xy(x, y, '|');
}

// print_food()
// ... 입력받은 위치에 뱀의 먹이를 출력한다.
//
void Display::print_food(Position pos)
{
	putchar_at_xy(pos.X, pos.Y, '#');
}

// print_snake()
// ... 뱀 모양을 화면에 출력한다.
//
void Display::print_snake(Snake snake)
{
	list<Position>::const_iterator iter = snake.body().begin();

	// 뱀의 머리를 출력한다.
	putchar_at_xy(iter->X, iter->Y, 'O');

	// 뱀의 몸통을 출력한다.
	while (++iter != snake.body().end())
		putchar_at_xy(iter->X, iter->Y, 'o');
}

// clear()
// ... 게임화면을 깨끗이 지운다.
//
void Display::clear()
{
	system("cls");
}