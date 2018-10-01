#include <iostream>
#include "../../include/snake.h"
#include "../../include/apple.h"
#include "../../include/textdisplay.h"
#include "../../include/map.h"
using namespace std;

Map *Map::mapInstance = nullptr;

Map::Map() {}

Map::~Map() {}

Map *Map::getInstance() {
	if (!mapInstance) mapInstance = new Map();
	return mapInstance;
}

void Map::deleteInstance() {
	delete mapInstance;
}

shared_ptr<Snake> Map::getSnake() { return theSnake; }

shared_ptr<Apple> Map::getApple() { return theApple; }

int Map::getScore() const { return theSnake->getLen(); }

void Map::init(const int w, const int h) {
	width = w;
	height = h;

	if (!theSnake) theSnake = make_shared<Snake>(width, height, 1, 1, 3);

	theApple = make_shared<Apple>(randGen());

	detachAll();
	td = make_shared<TextDisplay>(height, width);
    attach(td);
}

bool Map::isWall(const Posn &p) const {
	return p.x == 0 || p.x == width-1 
	|| p.y == 0 || p.y == height-1;
}

void Map::mapPrint() { notifyAll(); }

bool Map::isAlive() {
	// Snake hit any wall
	if (theSnake->getHead()->p.x == 0 
		|| theSnake->getHead()->p.x == width-1
		|| theSnake->getHead()->p.y == 0 
		|| theSnake->getHead()->p.y == height-1) return false;
	// Snake bites itself
	if (theSnake->isSnakeBody(theSnake->getHead()->p)) return false;
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
	shared_ptr<Posn> p = make_shared<Posn>(randX, randY);
	//Posn p = Posn(randX, randY);
	while(isWall(*p) || theSnake->isSnake(*p)) {
		p->x = (rand() % (width-2)) + 1;
		p->y = (rand() % (width-2)) + 1;
	}
	return *p;
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
	noDelay = !noDelay;
	nodelay(stdscr, noDelay);
}

// Wait for user input for reply or quit
bool Map::gamePending() {
	gamePause();
	int c;
	bool replay = true;
	while (1) {

		printf("pending");
		c = getch();
		if (c=='y' || c=='Y') {
			printf("replay");
			gameReplay();
		} else if (c=='n' || c=='N') {
			printf("done");
			gameGG();
			replay = false;
		} else {
			continue;
		}
	}
	gamePause();
	return replay;
}

void Map::gameReplay() {
	init(16, 16);
}

// Quit the game
void Map::gameGG() const {
	
}
