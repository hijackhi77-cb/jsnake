#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>

class Observer;

class Subject {
    std::vector<Observer *> display;
public:
    void attach(Observer *o);
    void detach(Observer *o);
    void detachAll();
    void notifyAll();
};

#endif
