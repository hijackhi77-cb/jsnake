#include <string.h>
#include "../../include/map.h"
#include "../../include/snake.h" // Node
#include "../../include/apple.h"
#include "../../include/posn.h"
#include "../../include/textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(int height, int width)
: height{height}, width{width} {
	initscr();
	cbreak();
	scrollok(stdscr, true);
	nodelay(stdscr, true);
	noecho();
	curs_set(0); // sets cursor to invisible

	int nlines, ncols, y0, x0;
	// TODO: responsive display size
	/*int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);*/
	
	/* mapWin */
	nlines = height;
	ncols = width;
	y0 = 0;
	x0 = 0;
	mapWin = newwin(nlines, ncols, y0, x0);
	int left, right, top, bottom, tlc, trc, blc, brc;
	left = right = (int)'|';
	top = bottom = (int)'-';
	tlc = trc = blc = brc = (int)'+';
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

	/* Testing for Memory Leaks
	 * 
	 * Perhaps you used a tool such as dmalloc or valgrind to check
	 * for memory leaks. It will normally report a lot of memory still
	 * in use. That is normal.
	 * 
	 * The ncurses configure script has an option, --disable-leaks,
	 * which you can use to continue the analysis. It tells ncurses
	 * to free memory if possible. However, most of the in-use memory
	 * is "permanent".
	 * 
	 * Any implementation of curses must not free the memory associated
	 * with a screen, since (even after calling endwin()), it must be
	 * available for use in the next call to refresh(). There are also
	 * chunks of memory held for performance reasons. That makes it hard
	 * to analyze curses applications for memory leaks. To work around
	 * this, build a debugging version of the ncurses library which frees
	 * those chunks which it can, and provides the _nc_free_and_exit()
	 * function to free the remainder on exit. The ncurses utility and
	 * test programs use this feature, e.g., via the ExitProgram() macro.
	 *
	 * http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks
	 */

	endwin();
}

void TextDisplay::notify(Subject *whoNotified) {
	Map *tempMap = static_cast<Map *>(whoNotified);
	update(tempMap);
}

void TextDisplay::update(Map *m) {
	shared_ptr<Snake> s = m->getSnake();
	shared_ptr<Apple> a = m->getApple();
	
	if (m->isAlive()) {
		// Update theApple
		mvwaddch(mapWin, a->y, a->x, (int)'O');
		// Clear lastTail
		mvwaddch(mapWin, s->getLastTail().y, s->getLastTail().x, (int)' ');
		// Update theSnake
		shared_ptr<Node> node = s->getHead();
		mvwaddch(mapWin, node->p.y, node->p.x, (int)'@');
		node = node->next;
		while (node) {
			mvwaddch(mapWin, node->p.y, node->p.x, (int)'*');
			node = node->next;
		}

		// Update score number
		const char *score = strdup(to_string(m->getScore()).c_str());
		mvwprintw(scoreWin, 2, 14, score);
	} else {
		// mvwprintw(win*, numRow, numCol, "hi")
		mvwprintw(mapWin, height/2, 0, "Good Game!");
	}

	wrefresh(mapWin);
	wrefresh(scoreWin);
}
