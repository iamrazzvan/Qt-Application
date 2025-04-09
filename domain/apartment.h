#ifndef LABORATOR_10_11_APARTMENT_H
#define LABORATOR_10_11_APARTMENT_H

#include <string>

#include "../exceptions/excepApartment.h"

using namespace std;

class Apartment {
private:
    int apartmentNumber;
    string ownerName;
    double surface;
    string apartmentType;

public:
    Apartment();
    Apartment(int apartmentNumber, string ownerName, double surface, string apartmentType);
    Apartment(const Apartment& apartment);

    int get_apartmentNumber() { return this->apartmentNumber; }
    string get_ownerName() { return this->ownerName; }
    double get_surface() { return this->surface; }
    string get_apartmentType() { return this->apartmentType; }

    void set_apartmentNumber(int new_apartmentNumber) { this->apartmentNumber = new_apartmentNumber; }
    void set_ownerName(string new_ownerName) { this->ownerName = new_ownerName; }
    void set_surface(double new_surface) { this->surface = new_surface; }
    void set_apartmentType(string new_apartmentType) { this->apartmentType = new_apartmentType; }

    static void validator(Apartment apartment);
};

#endif //LABORATOR_10_11_APARTMENT_H
