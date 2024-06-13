#include "Controller.h"

Controller::Controller(MyString FN) : Controller::Controller(){
      filename = FN;
      openFile(filename);
}

Controller::Controller() {
	adapter = Adapter();

	mode = 'n';
	filename = "untitled";

	model = Model();
	view = View();
}

void Controller::MainLoop(){
	while(mode != 'q'){
		view.updateStatus(mode);
		view.printLine();
		int input = adapter.getchar();
		handleInput(input);
	}

	adapter.~Adapter();
}

void Controller::handleInput(int c){
	switch(c){
		case KEY_LEFT:
			view.Left();
			return;
		case KEY_RIGHT:
			view.Right();
			return;
		case KEY_UP:
			view.Up();
			return;
		case KEY_DOWN:
			view.Down();
			return;
		case KEY_PPAGE:
			view.PageUp();
			return;
		case KEY_NPAGE:
			view.PageDown();
			return;
		case KEY_EXIT:
		case 27:
			if(mode == ':')
				view.restorePos();
			mode = 'n';
			return;
	}

	switch(mode){
		case 'n':
			proccesNavigation(c);
			break;
		case 'w':
			proccesInsert(c);
			break;
		case ':':
			proccesCommand(c);
			view.restorePos();
			break;
		case '/':
		case '?':
			proccessSearch(c);
			view.restorePos();
			break;
	}
}

void Controller::proccesNavigation(int c){
	char temp;
	string tmp;
	back:
	switch(c){
		case 'G':
			view.End();
			break;
		case 'g':
			if (adapter.getchar() == 'g')
				view.Home();
			break;
		case '^':
			view.moveStart();
			break;
		case '$':
			view.moveEnd();
			break;
		case 'w':
			view.wordEnd();
			break;
		case 'b':
			view.wordStart();
			break;
		case 'x':
			view.DeleteRight();
			break;
		case 'd':
			c = adapter.getchar();
			if (c == 'i'){
				if (adapter.getchar() == 'w')
					view.deleteWord();
			}
			if (c == 'd'){
				view.cutLine();
			}
			break;
		case 'y':
			c = adapter.getchar();
			if (c == KEY_ENTER or c == 10){
				view.copyLine();
			}
			if (c == 'w'){
				view.copyWord();
			}
			break;
		case 'p':
			view.insertBuffer();
			break;
		case 'I':
			view.moveStart();
			c = 'i';
			goto back;
		case 'S':
			view.moveEnd();
			c = 'i';
			goto back;
		case 'A':
			model.removeLine(view.y + view.offsetLine);
			view.moveStart();
			c = 'i';
			goto back;
		case 'r':
			view.removeChar();
			break;
		case 'i':
			mode = 'w';
			break;
		case ':':
		case '/':
		case '?':
			mode = c;
			break;
		case 's':
			saveFile(filename);
			break;
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			view.setXY(0, adapter.numOfLines() - 1);
			int num = c - '0';
			view.status.clear();
			statusHandleInput(c, 0);
			while((c = adapter.getchar()) != 'G'){
				if (c >= '0' and c <= '9'){
					num = num * 10 + (c - '0');
					statusHandleInput(c, 0);
				}
			}
			view.moveToLine(num - 1);
			break;
	}
}

void Controller::proccesInsert(int c){
	switch(c){
		case KEY_EXIT:
		case 27:
			mode = 'n';
			return;
		case 127:
		case KEY_BACKSPACE:
			view.BackSpace();
			break;
		case KEY_DC:
			view.DeleteRight();
			break;
		case KEY_ENTER:
		case 10:
			view.EnterKey();
			break;
		case KEY_BTAB:
		case KEY_CTAB:
		case KEY_STAB:
		case KEY_CATAB:
		case 9:
			view.TabKey();
			break;
		default:
			if (c > 31)
				view.AddChar(c);
			break;
	}
}

void Controller::statusHandleInput(int c, int border){
	switch(c){
		case KEY_LEFT:
			view.statusLeft(border);
			break;
		case KEY_RIGHT:
			view.statusRight();
			break;
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		case 127:
		case KEY_BACKSPACE:
			view.statusBackSpace(border);
			break;
		case KEY_DC:
			view.statusDelete();
			break;
		default:
			if (c > 31)
				view.statusAddChar(c);
			break;
	}
	view.printStatusLine();
}

void Controller::proccesCommand(int c){
	MyString temp;
	int i = 2;
	int num;
	vector <MyString> tempStr;
	while(1){
		if (c == KEY_EXIT or c == 27){
			mode = 'n';
			return;
		}
		if (c == KEY_ENTER or c == 10){
			switch (view.status[1])
			{
				case 'o':
					i = 2;
					while(view.status[i++] == ' ');
					i--;
					if (i == view.status.length()){
						view.updateStatus("No filename!");
						return;
					}
					filename = view.status.substr(i);
					openFile(view.status.substr(i));
					return;
				case 'x':
					saveFile(filename);
					mode = 'q';
					return;
				case 's':
					if (view.status[2] == 'e' and view.status[3] == 't' and view.status[4] == ' ' and view.status[5] == 'n' and view.status[6] == 'u' and view.status[7] == 'm' and view.status[8] == '\0'){
					view.setNum();				
					return;
                                 }
				case 'w':
					i = 2;
					while(view.status[i++] == ' ');
					i--;
					if (i == view.status.length()){
						saveFile(filename);
						return;
					}
					if (view.status[2] == 'q' and view.status[3] == '!' and view.status[4] == '\0'){
						saveFile(filename);
						mode = 'q';
						return;
					}
					saveFile(view.status.substr(i));
					return;
				case 'q':
					if (view.status[2] == '!'){
						mode = 'q';
						return;
					}
					if (view.status[2] == '\0'){
						saveFile(filename);
						mode = 'q';
						return;
					}
					view.updateStatus("Unknown command. Press any key");
					adapter.getchar();
					return;
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					i = 0;
					num = 0;
					while(view.status[++i] >= '0' and view.status[i] <= '9'){
						num = num * 10 + (view.status[i] - '0');
					}
					if (view.status[i] == '\0'){
						view.moveToLine(num - 1);
						view.storePos();
						return;
					}
					else {
						view.updateStatus("Unknown command. Press any key");
						adapter.getchar();
						return;
					}
					break;

				case 'h':
					//view.storePos();
					//view.printHelp();
					tempStr = model.lines;
					openFile("help");
					view.printLine();
					view.setXY(0, 0);
					view.offsetX = 0;
					view.offsetLine = 0;
					adapter.Move(view.y, view.x);
					while (1){
						bool ext = 0;
						c = adapter.getchar();
						switch(c){
							case KEY_UP:
							view.Up();
							view.printLine();
							break;
						case KEY_DOWN:
							view.Down();
							view.printLine();
							break;
						case KEY_LEFT:
							view.Left();
							view.printLine();
							break;
						case KEY_RIGHT:
							view.Right();
							view.printLine();
							break;
						default:
							ext = 1;
						}

						if (ext)
							break;
					}
					view.restorePos();
					model.lines = tempStr;
					view.printLine();
					return;

				default:
					view.updateStatus("Unknown command. Press any key");
					adapter.getchar();
					return;
					
			}
		}
		statusHandleInput(c, 1);
		c = adapter.getchar();
	}
}

void Controller::saveFile(MyString filename){
	ofstream fout(filename.data());
	if (fout.is_open()){
		for (int i = 0; i < model.lines.size(); i++){
			fout << model.lines[i].data(); //Надо сделать метод
			fout << "\n";
		}
		view.updateStatus("Saved! Press any key to continue");
		adapter.Move(adapter.numOfLines() - 1, view.status.length());
		adapter.getchar();
	}
	else
		view.updateStatus("Error: cannot open file!");
	fout.close();
}

void Controller::openFile(MyString filename){
	ifstream inFile(filename.data());
	if (inFile.is_open()){
		while(model.modelSize() > 0)
			model.removeLine(0);

		while(!inFile.eof()){
			string temp;
			getline(inFile, temp);  //Возможно придется добавить этот метод
			model.appendLine(temp);
		}
		inFile.close();
	}
	else {
		MyString stat = "Cannot open file ";
		stat += filename;
		stat += "! Press any key to continue";
		view.updateStatus(stat);
		adapter.Move(adapter.numOfLines() - 1, view.status.length());
		adapter.getchar();
	}
}

void Controller::proccessSearch(int c){
	view.setXY(1, adapter.numOfLines() - 1);
	view.offsetLine = 0;
	view.offsetX = 0;
	move(view.y, view.x);

	MyString search;

	while(1){
		if (c == KEY_EXIT or c == 27){
			mode = 'n';
			return;
		}
		if (c == KEY_ENTER or c == 10){
			view.searchLine();
			break;
		}

		statusHandleInput(c, 0);
		c = adapter.getchar();
	}

	while(1) {
		c = adapter.getchar();
		MyString tmp;
		switch(c){
		case KEY_EXIT:
		case 27:
			mode = 'n';
			return;
		case 'n':
			view.Right();
			view.storePos();
			view.Left();

			tmp = "/";
			tmp += view.status.substr(1);
			view.updateStatus(tmp);

			view.searchLine();
			break;
		case 'N':
			view.Left();
			view.storePos();
			view.Right();

			tmp = "?";
			tmp += view.status.substr(1);
			view.updateStatus(tmp);

			view.searchLine();
			break;
		}
	}
}
