#ifndef LABORATOR_10_11_EXCEPAPARTMENT_H
#define LABORATOR_10_11_EXCEPAPARTMENT_H

#include <string>

using namespace std;

class Exceptie {
private:
    string message;

public:
    Exceptie(string message) :
            message(message) {

    }
    const string& getMessage() const noexcept {
        return message;
    }
};

class ExceptieValidator : public Exceptie {
public:
    ExceptieValidator(string message) :
            Exceptie(message) {

    }
};

#endif //LABORATOR_10_11_EXCEPAPARTMENT_H
