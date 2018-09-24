#include <string.h>
#include "../map.h"
#include "../snake.h" // Node
#include "../apple.h"
#include "../posn.h"
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(int height, int width)
: height{height}, width{width} {
	initscr();
	cbreak();
	scrollok(stdscr, true);
	nodelay(stdscr, true);
	noecho();
	curs_set(0); // sets cursor to invisible

	int nlines, ncols, y0, x0, yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	/* mapWin */
	nlines = height;
	ncols = width;
	y0 = 0;
	x0 = 0;
	mapWin = newwin(nlines, ncols, y0, x0);
	int left, right, top, bottom, tlc, trc, blc, brc;
	left = right = (int)'|';
	top = bottom = (int)'--';
	tlc = trc = blc = brc = (int)' ';
	wborder(mapWin, left, right, top, bottom, tlc, trc, blc, brc);
	
	/* scoreWin */
	nlines = height;
	ncols = 17;
	y0 = 0;
	x0 = width - 1;
	scoreWin = newwin(nlines, ncols, y0, x0);
	wborder(scoreWin, left, right, top, bottom, tlc, trc, blc, brc);	
	mvwprintw(scoreWin, 2, 2, "Your Score: 0");

	refresh();
}

TextDisplay::~TextDisplay() {
	delwin(mapWin);
	delwin(scoreWin);
	endwin();
}

void TextDisplay::notify(Subject *whoNotified) {
	Map *tempMap = static_cast<Map *>(whoNotified);
	updateDisplay(tempMap);
}

void TextDisplay::updateDisplay(Map *m) {
	Snake *s = m->getSnake();
	Apple *a = m->getApple();
	// Update theApple
	mvwaddch(mapWin, a->y, a->x, (int)'O');
	// Clear lastTail
	mvwaddch(mapWin, s->getLastTail().y, s->getLastTail().x, (int)' ');
	// Update theSnake
	Node *node = s->getHead();
	mvwaddch(mapWin, node->p.y, node->p.x, (int)'@');
	node = node->next;
	while (node) {
		mvwaddch(mapWin, node->p.y, node->p.x, (int)'*');
		node = node->next;
	}

	const char *score = strdup(to_string(m->getScore()).c_str());
	mvwprintw(scoreWin, 2, 14, score);

	wrefresh(mapWin);
	wrefresh(scoreWin);
}
