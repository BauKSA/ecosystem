#include<Windows.h>

#include "functions.h"

void gotoxy(int x, int y) {
	HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cCoords;
	cCoords.X = x;
	cCoords.Y = y;

	SetConsoleCursorPosition(cHandle, cCoords);
}

void cursorVisible(bool visible) {
	HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cCursor;
	cCursor.bVisible = visible;
	cCursor.dwSize = 1;

	SetConsoleCursorInfo(cHandle, &cCursor);
}