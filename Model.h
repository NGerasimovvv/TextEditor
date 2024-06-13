#ifndef _MODEL_H_
#define _MODEL_H_
#include "MyString.h"
#include <iostream>
#include <vector>
#include <ncurses.h>
using namespace std;

class Model{
	public:
		Model();

		char table[28] = {' ', '!', '^', '&', '*', '(', ')', '-', '=', '+', '[', '{', ']', '}', '\\', '|', ',', '<', '.', '>', '/', '?', '`', '~', ';', ':', '\'', '\"'};

		void insertLine(MyString, int);
		void appendLine(MyString);
		void removeLine(int);
		MyString remTabs(MyString);

		void Insert(int, int, int, char);

		int lastLineSize();
		int modelSize();
		int lineSize(int line);

		int wordEnd(int line, int idx);
		int wordStart(int line, int idx);

		void deleteWord(int line, int start, int end);

		void copyToBuf(MyString line);
		void copyToBuf(int line);
		void insertBuf(int line, int idx);

		int* searchStr(MyString str, int X, int Y);
		int* searchBack(MyString str, int X, int Y);

		int findBack(MyString str, MyString sub, int X);

		friend class View;
		friend class Controller;

	private:
		vector<MyString> lines;
		MyString buffer;
		bool numOn;
		int len;
};

#endif
