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
	Mario p;
	p.setBoard(board);
	while (true) {
		p.draw();
		if (_kbhit()) {
			char key = _getch();
			if (key == ESC) break;
			p.keyPressed(key);
		}
		Sleep(60);
		p.erase();
		p.move();
	}
}
