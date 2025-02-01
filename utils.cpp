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

int checkArgs(int argc, char** argv, bool& isLoad, bool& isSave, bool& isSilent, bool& retFlag)
{
    retFlag = true;
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-load")
            isLoad = true;
        else if (std::string(argv[i]) == "-save")
            isSave = true;
        else if (std::string(argv[i]) == "-silent")
            isSilent = true;
    }
    if (isLoad && isSave)
    {
        std::cerr << "Error: Cannot use -load and -save together." << std::endl;
        return 1;
    }
    retFlag = false;
    return {};
}

void reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
    system("cls");
    std::cout << "Screen " << filename << " - " << message << '\n';
    std::cout << "Iteration: " << iteration << '\n';
    _getch();
}
