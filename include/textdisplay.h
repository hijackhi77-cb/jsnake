#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <iomanip>
#include <vector>
#include <ncurses.h> // WINDOW
#include "observer.h" // Inheritance from Observer

class Map;

class TextDisplay : public Observer {
	WINDOW *mapWin;
	WINDOW *scoreWin;
public:
	int height, width;
	TextDisplay(int height, int width);
	~TextDisplay();
	void notify(Subject *whoNotified) override;
	void update(Map *m);
};

#endif