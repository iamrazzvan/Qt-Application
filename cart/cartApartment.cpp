#include "cartApartment.h"

void CartApartment::emptyCart() {
    vectorApartmentsCart.clear();
    notify();
}

void CartApartment::addApartmentToCart(Apartment apartment) {
    vectorApartmentsCart.push_back(apartment);
    notify();
}

vector<Apartment> CartApartment::getCart() {
    return vectorApartmentsCart;
}

void CartApartment::exportCart(string fileName) {
    fileName += ".csv";
    ofstream fout(fileName);
    for (auto x : this->vectorApartmentsCart) {
        string str = std::to_string(x.get_apartmentNumber()) + "," + x.get_ownerName() + "," + std::to_string(x.get_surface()) + "," + x.get_apartmentType() + "\n";
        fout << str;
    }
}