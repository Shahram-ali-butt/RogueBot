#include <windows.h>
#include <string>
#include "console.h"
#include "config.h"

using namespace std;

void gotoxy(int x, int y) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x >= boundaryLength) x = boundaryLength - 1;
    if (y >= boundaryHeight) y = boundaryHeight - 1;

    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

char getCharAtxy(short int x, short int y){
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}

void setConsoleSize(short width, short height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(hOut, bufferSize);

    SMALL_RECT windowSize;
    windowSize.Left   = 0;
    windowSize.Top    = 0;
    windowSize.Right  = width;
    windowSize.Bottom = height;
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void hideCursor(){
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void generateColors(int color){
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void initConsole(short width, short height) {
    setConsoleSize(width, height);
    disableScroll();
    disableTextWrap();
    hideCursor();
}

string getExeDir() {
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    string path(buffer);
    return path.substr(0, path.find_last_of("\\/"));
}

void disableScroll(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);

    info.dwSize.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
    info.dwSize.X = info.srWindow.Right - info.srWindow.Left + 1;

    SetConsoleScreenBufferSize(hOut, info.dwSize);
}

void disableTextWrap(){
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
    SetConsoleMode(hOut, mode);
}
