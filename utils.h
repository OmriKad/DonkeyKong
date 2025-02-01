#pragma once
#include <string>
void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
void clearScreen();
char getKeyFromUser();
int checkArgs(int argc, char** argv, bool& isLoad, bool& isSave, bool& isSilent, bool& retFlag);
void reportResultError(const std::string& message, const std::string& filename, size_t iteration);
