#ifndef LABORATOR_10_11_OBSERVER_H
#define LABORATOR_10_11_OBSERVER_H

#include <algorithm>
#include <vector>

class Observer {
    public:
        virtual void update() = 0;
};

class Observable {
    private:
        std::vector<Observer*> observers;

    public:
        void addObserver(Observer* observer) {
            observers.push_back(observer);
        }

        void removeObserver(Observer* observer) {
            observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
        }

        void notify() {
            for (auto observer : observers) {
                observer->update();
            }
        }
};

#endif //LABORATOR_10_11_OBSERVER_H
