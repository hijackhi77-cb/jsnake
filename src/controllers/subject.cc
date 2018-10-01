#include <iostream>
#include "../../include/observer.h"
#include "../../include/subject.h"
using namespace std;

void Subject::attach(shared_ptr<Observer> o) { display.push_back(o); }

void Subject::detach(shared_ptr<Observer> o) { display.push_back(o); }

void Subject::detachAll() { display.clear(); }

void Subject::notifyAll() {
    for (auto &o : display) o->notify(this);
}
