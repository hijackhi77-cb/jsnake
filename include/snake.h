#ifndef _SNAKE_H_
#define _SNAKE_H_
#include "posn.h"
#include <memory>

// 0, 1, 2, 3, 4
enum Direction { N, W, E, S, UNKNOWN };

struct Node {
	Posn p;
	std::shared_ptr<Node> prev;
	std::shared_ptr<Node> next;
	int dir = Direction::UNKNOWN;
	Node();
	Node(const Posn &p, const int dir);
};

class Snake {
	int width, height;
	std::shared_ptr<Node> head = nullptr;
	std::shared_ptr<Node> tail = nullptr;
	// len = #edges = #node - 1
	unsigned len = 0;
	static Posn lastTail;
public:
	Snake(int w, int h, int x, int y, int dir);
	~Snake();
	std::shared_ptr<Node> getHead() const;
	std::shared_ptr<Node> getTail() const;
	int getLen() const;
	Posn &getLastTail() const;
	// TODO: void init(int w, int h, int x, int y, int dir);
	bool isSnakeBody(Posn &p) const;
	bool isSnake(Posn &p) const;
	void grow(const int step = 1);
	void move(const int dir, const int step);
	void changeDir(const int dir);
	void forward(const int step = 1);
};

#endif