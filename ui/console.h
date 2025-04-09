#ifndef LABORATOR_10_11_CONSOLE_H
#define LABORATOR_10_11_CONSOLE_H

#include <iostream>
#include <unordered_map>

#include "../exceptions/excepApartment.h"
#include "../service/srvApartment.h"

using namespace std;

class Console {
    private:
        SrvApartment& service;

    public:
        Console(SrvApartment& service) : service{ service } {}

        void run();
};

#endif //LABORATOR_10_11_CONSOLE_H
