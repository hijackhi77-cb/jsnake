#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <memory>

class Observer;

class Subject {
    std::vector<std::shared_ptr<Observer>> display;
public:
    void attach(std::shared_ptr<Observer> o);
    void detach(std::shared_ptr<Observer> o);
    void detachAll();
    void notifyAll();
};

#endif