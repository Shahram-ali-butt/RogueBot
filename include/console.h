#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void initConsole(short width, short height);
void generateColors(int color);
void hideCursor();
std::string getExeDir();
void disableScroll();
void disableTextWrap();

#endif
