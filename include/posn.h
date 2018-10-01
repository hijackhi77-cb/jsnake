#ifndef _POSN_H_
#define _POSN_H_

struct Posn { 
	int x; 
	int y; 
	Posn();
	Posn(int x, int y);
	bool operator==(const Posn &other) const;
};

#endif