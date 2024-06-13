#include "Adapter.h"

Adapter::Adapter(){
    initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);
}

Adapter::~Adapter(){
    refresh();
	endwin();
}

void Adapter::Move(int row, int col){
    move(row, col);
}

int Adapter::getchar(){
    return getch();
}

void Adapter::signal(){
    beep();
}

int Adapter::numOfLines(){
    return LINES;
}

int Adapter::windowWidth(){
    return COLS;
}

void Adapter::printStr(MyString str, int i){
    mvprintw(i, 0, "%s\n", str.data());
}

void Adapter::printStr(MyString str, int i, int len){
    mvprintw(i, len, "%s\n", str.data());
}

void Adapter::printStr(int i, int offsetLine) {
    mvprintw(i, 0, "%d", i+1+offsetLine);
}

void Adapter::clearLine(){
    clrtoeol();
}
