#include "Controller.h"

#define model Controller::model
#define adapter Controller::adapter

View::View(){
	x = 0;
	y = 0;
	len = 0;
	offsetLine = 0;
	offsetX = 0;
	status = "Navigation mode";
	model.appendLine("");
}

bool View::Up(){
	if (y > 0)
		y--;
	else if (y == 0 && offsetLine > 0)
		offsetLine--;
	else{
		adapter.signal();
		return 0;
	}
	if (curX > model.lineSize(curLine) + len){
		x -= curX - model.lineSize(curLine) + len;
		if (x < 0){
			x = model.lineSize(curLine) + len;
			offsetX = 0;
		}
		if (x >= WIDTH){
			offsetX = x - WIDTH + 1;
			x = WIDTH - 1;
		}
	}
	return 1;
}

bool View::Down(){
	if (y < WNDW - 1 && curLine < model.modelSize() - 1)
		y++;
	else if (y == WNDW - 1 && model.modelSize() - 1 > curLine)
		offsetLine++;
	else{
		adapter.signal();
		return 0;
	}
	if (curX > model.lineSize(curLine) + len){
		x -= curX - model.lineSize(curLine) + len;
		if (x < 0){
			x = model.lineSize(curLine) + len;
			offsetX = 0;
		}
		if (x >= WIDTH){
			offsetX = x - WIDTH + 1;
			x = WIDTH - 1;
		}
	}
	return 1;
}

bool View::Left(){
	if (x > 0 + len)
		x--;
	else if (x == 0 + len){
		if (offsetX > 0){
			offsetX--;
			return 1;
		}

		if (y > 0){
			y--;
			x = model.lineSize(curLine) + len;
			if (x >= WIDTH){
				offsetX = x - WIDTH + 1;
				x = WIDTH - 1;
			}
		}
		else if (y == 0 && offsetLine > 0){
			offsetLine--;
			x = model.lineSize(curLine) + len;
			if (x >= WIDTH){
				offsetX = x - WIDTH + 1;
				x = WIDTH - 1;
			}
		}
		else{
			adapter.signal();
			return 0;
		}
	}
	return 1;
}

bool View::Right(){
	if (curX < model.lineSize(curLine) + len){
		if (x + 1 >= WIDTH)
			offsetX++;
		else
			x++;
	}
	else if (curX == model.lineSize(curLine) + len && curLine < model.modelSize() - 1){
		if (y < WNDW)
			y++;
		else
			offsetLine++;
		x = 0 + len;
		offsetX = 0;
	}
	else{
		adapter.signal();
		return 0;
	}
	return 1;
}

void View::PageUp(){
	if (offsetLine > WNDW) offsetLine -= WNDW;
	else if (offsetLine != 0)
		offsetLine = 0;
	else adapter.signal();
	if (curX > model.lineSize(curLine)){
		x -= curX - model.lineSize(curLine);
		if (x < 0){
			x = model.lineSize(curLine);
			offsetX = 0;
		}
		if (x >= WIDTH){
			offsetX = x - WIDTH + 1;
			x = WIDTH - 1;
		}
	}
}

void View::PageDown(){
	if (offsetLine + WNDW * 2 + 2 <= model.modelSize()) 
		offsetLine += WNDW;

	else if (offsetLine + WNDW < model.modelSize())
		offsetLine = model.modelSize() - WNDW;
	else
		adapter.signal();
	if (curX > model.lineSize(curLine)){
		x -= curX - model.lineSize(curLine);
		if (x < 0){
			x = model.lineSize(curLine);
			offsetX = 0;
		}
		if (x >= WIDTH){
			offsetX = x - WIDTH + 1;
			x = WIDTH - 1;
		}
	}
}

void View::Home(){
	if (offsetLine != 0){
		offsetLine = 0;
		if (curX > model.lineSize(curLine)){
			x -= curX - model.lineSize(curLine);
			if (x < 0){
				x = model.lineSize(curLine);
				offsetX = 0;
			}
			if (x >= WIDTH){
				offsetX = x - WIDTH + 1;
				x = WIDTH - 1;
			}
		}
	}
	else adapter.signal();
}

void View::End(){
	if (model.modelSize() > WNDW){
		offsetLine = model.modelSize() - WNDW;
		if (curX > model.lineSize(curLine)){
			x -= curX - model.lineSize(curLine);
			if (x < 0){
				x = model.lineSize(curLine);
				offsetX = 0;
			}
			if (x >= WIDTH){
				offsetX = x - WIDTH + 1;
				x = WIDTH - 1;
			}
	}
	}
	else adapter.signal();
}

void View::moveStart(){
	x = 0 + len;
	offsetX = 0;
}

void View::moveEnd(){
	x = model.lineSize(curLine)+len;
	offsetX = 0;
	if (x >= WIDTH){
		offsetX = x - WIDTH + 1;
		x = WIDTH - 1;
	}
}

void View::moveToLine(int line){
	if (line > model.modelSize()){
		adapter.signal();
		return;
	}
	if (line > offsetLine + WNDW or line < offsetLine){
		if (line > model.modelSize() - WNDW){
			offsetLine = model.modelSize() - WNDW;
			y = line - offsetLine;
		}
		else {
			offsetLine = line;
			y = 0;
		}
	}
	else
		y = line - offsetLine;

	x = 0;
	offsetX = 0;
}

void View::wordEnd(){
	if (curX == model.lineSize(curLine) + len){
		if (!Right())
			return;
	}
	int pos = curX + len;

	while(1){
		pos = model.wordEnd(curLine, pos);
		if (pos == -1 or pos == curX or pos == 0 + len or model.lines[curLine][pos] == model.lines[curLine][pos - 1]){
			if (!Right())
				return;
		}
		else{
			x = pos;
			offsetX = 0;
			if (x >= WIDTH){
				offsetX = x - WIDTH + 1;
				x = WIDTH - 1;
			}
			return;
		}
		pos = curX + len;
	}
}

void View::wordStart(){
	if (x == 0 + len){
		if (!Left())
			return;
	}
	int pos = curX - len;
	while(1){
		pos = model.wordStart(curLine, pos) - len;	
		if (pos < 0 or pos == curX or pos == model.lineSize(curLine) or model.lines[curLine][pos] == model.lines[curLine][pos + 1]){	
			if (!Left())
				return;
		}
		else {
			x = pos;
			offsetX = 0;
			if (x >= WIDTH){
				offsetX = x - WIDTH + 1;
				x = WIDTH - 1;
			}
			return;
		}
		pos = curX - len;
	}
}

void View::deleteWord(){

	bool ok = false;
	for (int i = 0; i < 28; i++){
		if (model.lines[curLine][curX] == model.table[i])
			ok = ok + true;
	}
	if (ok){
		adapter.signal();
		return;
	}

	int start = model.wordStart(curLine, curX);
	if (start == -1)
		start = 0;


	int end = model.wordEnd(curLine, curX);
	if (end == -1)
		end = model.lineSize(curLine) - 1;


	model.deleteWord(curLine, start, end);
	x = start;
	if (x >= WIDTH){
		offsetX = x - WIDTH + 1;
		x = WIDTH - 1;
	}
}

void View::BackSpace(){
	if (x == 0 + len && y != 0){
		x = model.lines[curLine - 1].length() + len;
		if (x >= WIDTH){
			offsetX = x - WIDTH + 1;
			x = WIDTH - 1;
		}

		model.lines[curLine - 1] += model.lines[curLine];
		deleteLine();
		if (offsetLine > 0)
			offsetLine--;
		else
			Up();
	}
	else /*if (x > 0 && y >= 0)*/{
		if (Left())
			model.lines[curLine].erase(curX, 1);
	}
	//else
	//	adapter.signal();
}

void View::DeleteRight(){
	if(curX == model.lineSize(curLine) and curLine != model.modelSize() - 1){
		model.lines[curLine] += model.lines[curLine + 1];
		deleteLine(curLine + 1);
	}
	else if (curX != model.lineSize(curLine))
		model.lines[curLine].erase(curX, 1);
	else
		adapter.signal();
}

void View::TabKey(){
	model.Insert(curLine, curX, 4, ' ');
	x += 4;
	if (x >= WIDTH){
		offsetX = x - WIDTH + 1;
		x = WIDTH - 1;
	}
}

void View::EnterKey(){
	if (curX < model.lineSize(curLine)){
		model.insertLine(model.lines[curLine].substr(curX, model.lineSize(curLine) - curX), curLine + 1);
		model.lines[curLine].erase(curX, model.lineSize(curLine) - curX);
	}
	else{
		model.insertLine("", curLine + 1);
	}
	x = 0 + len;
	offsetX = 0;
	Down();
}

void View::deleteLine(){
	model.removeLine(curLine);
}

void View::deleteLine(int cord){
	model.removeLine(cord);
}

void View::AddChar(char c){
	model.Insert(curLine, x + offsetX, 1, c);
	if (x + 1 >= WIDTH)
		offsetX++;
	else
		x++;
}

void View::removeChar(){
	updateStatus('r');

	int temp;
	while((temp = adapter.getchar()) < 32);

	char tmp[] = {char(temp), '\0'};
	updateStatus(MyString("r") + MyString(tmp));
	if (curX-len != 0)
		model.lines[curLine].replace(curX-1-len, 1, tmp);
	else {
		model.lines[curLine].insert(curX-len, tmp);
		Right();
	}
}

int View::setNum() {
	int n = model.modelSize();
	MyString tmp = to_string(n);
	len = tmp.size() + 1;
	if (!numOn) {
		numOn = 1;
	}
	else {
		numOn = 0;
		len = 0;
	}
}

void View::printLine(){
	for (int i = 0; i < WNDW; i++){
		if (i + offsetLine >= model.modelSize()){
			adapter.Move(i, 0);
			adapter.clearLine();
		}
		else
		{
			if (model.lineSize(i + offsetLine) >= offsetX)
				{
				if (numOn) {
					adapter.Move(i, 0);
					adapter.clearLine();
					adapter.printStr(i, offsetLine);
				}
				adapter.printStr(model.lines[i + offsetLine].substr(offsetX, WIDTH - 1), i, len);
			} 
			else
				adapter.Move(i, 0);
			adapter.clearLine();
		}
	}
	adapter.Move(y, x);
}

void View::printStatusLine(){
	attron(A_REVERSE);
	adapter.printStr(status, LINES - 1);
	clrtoeol();
	attroff(A_REVERSE);
	adapter.Move(y, x);
}

void View::updateStatus(char mode){
	switch(mode){
		case 'n':
			status = "Navigation mode";
			break;
		case 'w':
			status = "Write mode";
			break;
		case ':':
		case '/':
		case '?':
			storePos();
			status = MyString(1, mode);
			printStatusLine();
			x = 1;
			y = LINES - 1;
			adapter.Move(y, x);
			return;
		case 'q':
			status = "To quit press Enter";
			break;
		case 'r':
			status = mode;
	}

	auto cols = status.find("\tCOL");
	if (cols != -1)
		status.erase(cols, status.size());

	status += "\tCOL: " + to_string(x + offsetX) + "\tROW: " + to_string(curLine + 1) + "\toffsetX: " + to_string(offsetX) + "\toffsetY: " + to_string(offsetLine);

	printStatusLine();
}

void View::updateStatus(MyString extra){
	status.clear();
	status = extra.data();
	printStatusLine();
}

void View::statusBackSpace(int bolder){
	if (x > bolder){
		status.erase(x-1, 1);
		x--;
	}
	else adapter.signal();
}

void View::statusDelete(){
	if (x < status.length())
		status.erase(x, 1);
	else adapter.signal();
}

void View::statusAddChar(int c){
	status.insert(x, 1, char(c));
	x++;
}

void View::statusLeft(int border){
	if (x > border){
		x--;
		adapter.Move(y, x);
	}
	else adapter.signal();
}

void View::statusRight(){
	if (x < status.length()){
		x++;
		adapter.Move(y, x);
	}
	else adapter.signal();
}

void View::copyLine(){
	model.copyToBuf(curLine);
}

void View::cutLine(){
	copyLine();
	model.removeLine(curLine);
	moveStart();
}

void View::copyWord(){
	int start = model.wordStart(curLine, curX);
	int end = model.wordEnd(curLine, curX);
	
	MyString bufLine = model.lines[curLine].substr(start, end - start + 1);
		
	model.copyToBuf(bufLine);
	
}

void View::insertBuffer(){
	model.insertBuf(curLine, curX-len);

	x = curX + model.buffer.size();
	if (x >= WIDTH){
		offsetX = x - WIDTH + 1;
		x = WIDTH - 1;
	}
	EnterKey();
	Left();
}

void View::storePos(){
	x_ = x + len;
	y_ = y;
	offL = offsetLine;
	offX = offsetX;
}

void View::restorePos(){
	x = x_ + len;
	y = y_;
	offsetLine = offL;
	offsetX = offX;
}

void View::setXY(int X, int Y){
	x = X;
	y = Y;
}

void View::searchLine(){
	int *res;

	MyString search = status.substr(1);

	if (status[0] == '/')
		res = model.searchStr(search, x_, y_ + offL);
	if (status[0] == '?')
		res = model.searchBack(search, x_, y_ + offL);
	
	if (res[0] != -1){
		moveToLine(res[1]);
		printLine();
		adapter.Move(y, (x = res[0]));
		//cout << y << " " << x << " " << offsetLine << endl;
		storePos();
	}

	return;
}

void View::printHelp(){
	ifstream inFile("help");
	if (inFile.is_open()){
		int i = 0;
		while(!inFile.eof()){
			string temp;
			getline(inFile, temp);
			adapter.printStr(MyString(temp), i);
			adapter.clearLine();
			i++;
		}
		inFile.close();
	}
}
