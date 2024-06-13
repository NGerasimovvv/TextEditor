#pragma once
#ifndef _ADAPTER_H_
#define _ADAPTER_H_
#include <ncurses.h>
#include <iostream>
#include "MyString.h"

class Adapter{
public:
    Adapter();
    ~Adapter();
    void Move(int row, int col);
    void signal();
    int getchar();
    static int numOfLines();
    static int windowWidth();
    void printStr(MyString str, int i);
    void printStr(MyString str, int i, int len);
    void printStr(int i, int offsetLine);
    void clearLine();

};

#endif //_ADAPTER_H_
