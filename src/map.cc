#include <iostream>
#include "snake.h"
#include "apple.h"
#include "view/textdisplay.h"
#include "map.h"
using namespace std;

Map *Map::mapInstance = nullptr;

Map::Map() {}

Map::~Map() {}

Map *Map::getInstance() {
	if (!mapInstance) mapInstance = new Map();
	return mapInstance;
}

void Map::deleteInstance() {
	delete theSnake;
	delete theApple;
	delete td;

	delete mapInstance;
	mapInstance = nullptr;
}

Snake *Map::getSnake() { return theSnake; }

Apple *Map::getApple() { return theApple; }

int Map::getScore() const { return theSnake->getLen(); }

void Map::init(const int w, const int h) {
	width = w;
	height = h;

	theSnake = new Snake(width, height, 1, 1, 3);

	theApple = new Apple(randGen());

	detachAll();
	td = new TextDisplay(height, width);
    attach(td);
}

bool Map::isWall(const Posn &p) const {
	return p.x == 0 || p.x == width-1 || p.y == 0 || p.y == height-1;
}

void Map::mapPrint() { notifyAll(); }

bool Map::isAlive() {
	// Snake hit any wall
	if (theSnake->getHead()->p.x == 0 
		|| theSnake->getHead()->p.x == width-1
		|| theSnake->getHead()->p.y == 0 
		|| theSnake->getHead()->p.y == height-1) return false;
	// Snake bets itself
	Node *node = theSnake->getHead();
	if (theSnake->isSnakeBody(node->p)) return false;
	return true;
}

bool Map::isEating() {
	if (theApple->x == theSnake->getHead()->p.x
		&& theApple->y == theSnake->getHead()->p.y) return true;
	return false;
}

Posn &Map::randGen() const {
	int randX = (rand() % width-2) + 1;
	int randY =	(rand() % width-2) + 1;
	Posn &p = *(new Posn(randX, randY));
	while(isWall(p) || theSnake->isSnake(p)) {
		p.x = (rand() % (width-2)) + 1;
		p.y = (rand() % (width-2)) + 1;
	}
	return p;
}

bool Map::check() {
	if (!isAlive()) {
		return false;
	} else if (isEating()) {
		theApple->remove();
		theSnake->grow();
		theApple->generate(randGen());
	}
	return true;
}

void Map::gamePause() const {
	static bool noDelay = true;
	if (noDelay) {
		noDelay = false;
	} else {
		noDelay = true;
	}
	nodelay(stdscr, noDelay);
}

void Map::gameGG() const {
	
}
