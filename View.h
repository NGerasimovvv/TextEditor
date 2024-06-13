#ifndef _VIEW_H_
#define _VIEW_H_
#include "MyString.h"
#include <iostream>

class View{
	private:
	#define curLine (y + offsetLine) //A "pointer" to a current line among whole vector of lines
	#define curX (x + offsetX)
	#define WNDW (Adapter::numOfLines() - 2) //Size of a window which displays text
	#define WIDTH (adapter.windowWidth())
	#define NLINES (adapter.numOfLines())
		int x, y;
		int x_, y_;
		int offsetLine, offsetX;
		int offL, offX;
		MyString status;

		int len = 0;
		bool numOn;

		int setNum();

		bool Up();
		bool Down();
		bool Left();
		bool Right();

		void PageUp();
		void PageDown();

		void Home();
		void End();

		void moveStart();
		void moveEnd();
		void moveToLine(int line);

		void wordEnd();
		void wordStart();
		void deleteWord();

		void BackSpace();
		void DeleteRight();
		void EnterKey();
		void TabKey();

		void statusBackSpace(int);
		void statusDelete();
		void statusAddChar(int);

		void removeChar();

		void statusLeft(int border);
		void statusRight();

		void AddChar(char);
		void deleteLine();
		void deleteLine(int);

		void copyLine();
		void cutLine();
		void copyWord();
		void insertBuffer();

		void storePos();
		void restorePos();
		void setXY(int X, int Y);

	public:
		View();

		friend class Controller;

		void printLine();
		void printStatusLine();
		void updateStatus(char);
		void updateStatus(MyString);

		void searchLine();
		void next(char nN);

		void printHelp();
};

#endif
