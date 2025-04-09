#include "apartment.h"

Apartment::Apartment() {
    apartmentNumber = 0;
    ownerName = "\0";
    surface = 0;
    apartmentType = "\0";
}

Apartment::Apartment(int apartmentNumber, string ownerName, double surface, string apartmentType) {
    this->apartmentNumber = apartmentNumber;
    this->ownerName = ownerName;
    this->surface = surface;
    this->apartmentType = apartmentType;
}

Apartment::Apartment(const Apartment& apartment) {
    apartmentNumber = apartment.apartmentNumber;
    ownerName = apartment.ownerName;
    surface = apartment.surface;
    apartmentType = apartment.apartmentType;
}

void Apartment::validator(Apartment apartment) {
    string errors;
    if (apartment.get_apartmentNumber() < 0)
        errors += "Apartment number is negative\n";
    if (apartment.get_ownerName().length() == 0)
        errors += "Owner name is empty\n";
    if (apartment.get_apartmentType().length() == 0)
        errors += "Apartment type is empty\n";
    if (apartment.get_surface() < 0) {
        errors += "Surface is negative\n";
    }
    if (errors.length() > 0)
        throw ExceptieValidator(errors);
}