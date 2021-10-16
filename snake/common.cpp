#include <iostream>
#include <Windows.h>

typedef COORD Position;

void go_to_xy(int x, int y) {
	COORD positoin = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), positoin);
}

void putchar_at_xy(int x, int y, char ch) {
	COORD position = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	putchar(ch);
}