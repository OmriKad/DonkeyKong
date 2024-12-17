#include <iostream>
#include <windows.h>
#include <conio.h>
#include "utils.h"


// Using functions provieded from Amir Kirsh example.
void gotoxy(int x, int y) 
{
    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = x; // Set the X coordinate 
    coord.Y = y; // Set the Y coordinate 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void clearScreen()
{
    system("cls");
}

char getKeyFromUser() 
{
    char keyPressed = 0;

    while (true) {
        if (_kbhit()) {
            keyPressed = _getch();
            return keyPressed;
        }
    }
}