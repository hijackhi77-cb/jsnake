#include "posn.h"

Posn::Posn() {}

Posn::Posn(int x, int y) : x{x}, y{y} {}

bool Posn::operator==(const Posn &other) const {
	return x==other.x && y==other.y;
}
