#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "View.h"
#include "Model.h"
#include "Adapter.h"
#include <fstream>

using namespace std;

class Controller {
	public:
		Controller();
		Controller(MyString);

		void MainLoop();

		inline static Model model;
		inline static Adapter adapter;
		View view;

	private:
		char mode;
		MyString filename, nullStr = "";

		void handleInput(int);
		void proccesNavigation(int);
		void proccesInsert(int);
		void proccesCommand(int);
		void statusHandleInput(int, int);
		void saveFile(MyString);
		void openFile(MyString);

		void proccessSearch(int);

};

#endif
