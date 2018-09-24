#include <unistd.h> // usleep
#include <iostream>
#include "map.h"
#include "snake.h"
#include "apple.h"
#include "view/textdisplay.h"
using namespace std;

int main(int argc, char *argv[]) {
	int w = 16;
	int h = 16;

	for (int i=1; i<argc ; ++i) {
		istringstream arg(argv[i]);
		string flag;
		arg >> flag;
		if(flag == "-w") {
			w = stoi(argv[++i]);
		} else if (flag == "-h") {
			h = stoi(argv[++i]);
		} else {
			cerr << "JSnake starts failed: invalid flags" << endl;
			return 1;
		}
	}

	Map::getInstance()->init(w, h);
	Map::getInstance()->mapPrint();

	int c;
	while (1) {
		usleep(150000);
		if ((c=getch()) == 27 && (c=getch()) == 91) {
			switch(c=getch()) {
				case 65: // UP
					Map::getInstance()->getSnake()->changeDir(N);
				break;
				case 66: // DOWN
					Map::getInstance()->getSnake()->changeDir(S);
				break;
				case 67: // RIGHT
					Map::getInstance()->getSnake()->changeDir(E);
				break;
				case 68: // LEFT
					Map::getInstance()->getSnake()->changeDir(W);
				break;
			}	
		} else if (c == (int)'w' || c == (int)'W') {
			Map::getInstance()->getSnake()->changeDir(N);
		} else if (c == (int)'s' || c == (int)'S') {
			Map::getInstance()->getSnake()->changeDir(S);
		} else if (c == (int)'d' || c == (int)'D') {
			Map::getInstance()->getSnake()->changeDir(E);
		} else if (c == (int)'a' || c == (int)'A') {
			Map::getInstance()->getSnake()->changeDir(W);
		} else if (c == (int)' ') { 
			Map::getInstance()->gamePause();
			c = getch();
			while (c != (int)' ') { c = getch(); }
			Map::getInstance()->gamePause();
		} else if (c == (int)'q') {
			break;
		}

		Map::getInstance()->getSnake()->forward();
		if (Map::getInstance()->check()) {
			Map::getInstance()->mapPrint();
		} else {
			break;
		}
	}

	Map::getInstance()->deleteInstance();
	endwin();
	return 0;
}
