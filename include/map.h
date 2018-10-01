#ifndef _MAP_H_
#define _MAP_H_
#include <vector>
#include "subject.h" // Inheritance from Subject
#include <memory>

struct Posn;
class Snake;
class Apple;
class TextDisplay;

class Map : public Subject {
	int width;
	int height;
	std::shared_ptr<Snake> theSnake;
	std::shared_ptr<Apple> theApple;
	std::shared_ptr<TextDisplay> td;
	// Singleton pattern is used here
	static Map *mapInstance;
	// Private constructor to prevent instancing
	Map();
	~Map();
public:
	static Map *getInstance();
	void deleteInstance();
	std::shared_ptr<Snake> getSnake();
	std::shared_ptr<Apple> getApple();
	int getScore() const;
	void init(const int w, const int h);
	bool isWall(const Posn &p) const;
	void mapPrint();
	bool isAlive();
	bool isEating();
	bool check();
	Posn &randGen() const;
	void gamePause() const;
	bool gamePending();
	void gameReplay();
	void gameGG() const;
};

#endif