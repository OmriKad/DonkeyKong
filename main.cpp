#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Board.h"
#include "utils.h"
#include "Mario.h"

// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario m;
	m.setBoard(board);
	while (true) {
		board.reset();
		m.draw();
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) break;
			m.keyPressed(key);
		}
		Sleep(60);
		m.erase();
		m.move();
	}
}
