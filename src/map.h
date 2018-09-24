#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include "subject.h" // inheritance from Subject

struct Posn;
class Snake;
class Apple;
class TextDisplay;

class Map : public Subject {
	int width;
	int height;
	Snake *theSnake;
	Apple *theApple;
	TextDisplay *td;
	// Singleton pattern is used here
	static Map *mapInstance;
	// Private constructor to prevent instancing
	Map();
	~Map();
public:
	static Map *getInstance();
	void deleteInstance();
	Snake *getSnake();
	Apple *getApple();
	int getScore() const;
	void init(const int w, const int h);
	bool isWall(const Posn &p) const;
	void mapPrint();
	bool isAlive();
	bool isEating();
	bool check();
	Posn &randGen() const;
	void gamePause() const;
	void gameGG() const;
};

#endif