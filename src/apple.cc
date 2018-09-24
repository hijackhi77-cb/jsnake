#include "posn.h"
#include "apple.h"

Apple::Apple(const int x, const int y) : x{x}, y{y} {}

Apple::Apple(const Posn &p) : x{p.x}, y{p.y} {}

void Apple::generate(int x, int y) {
	this->x = x;
	this->y = y;
}

void Apple::generate(const Posn &p) {
	this->x = p.x;
	this->y = p.y;
}

void Apple::remove() {
	this->x = 0;
	this->y = 0;
}
