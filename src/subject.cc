#include <iostream>
#include "view/observer.h"
#include "subject.h"
using namespace std;

void Subject::attach(Observer *o) { display.push_back(o); }

void Subject::detach(Observer *o) { display.push_back(o); }

void Subject::detachAll() { display.clear(); }

void Subject::notifyAll() {
    for (auto &o : display) o->notify(this);
}
