#ifndef _APPLE_H_
#define _APPLE_H_

struct Apple {
	int x;
	int y;
	Apple(const int x, const int y);
	Apple(const Posn &p);
	void generate(int x, int y);
	void generate(const Posn &p);
	void remove();
};

#endif