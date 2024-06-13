#include "Controller.h"


int main(int argc, char* argv[]) {
	Controller controller;
	
	if (argc > 1)
		controller = Controller(argv[1]);
	else{
		cout << "Make controller" << endl;
		controller = Controller();
	}

	controller.MainLoop();

	return 0;
}
