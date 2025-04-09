#ifndef LABORATOR_10_11_CARTAPARTMENT_H
#define LABORATOR_10_11_CARTAPARTMENT_H

#include <fstream>
#include <string>
#include <vector>

#include "../Observer.h"
#include "../domain/apartment.h"

using namespace std;

class CartApartment : public Observable {
    private:
        vector<Apartment> vectorApartmentsCart;

    public:
        void emptyCart();

        void addApartmentToCart(Apartment apartment);

        vector<Apartment> getCart();

        //int getCartLength();

        void exportCart(string fileName);
};

#endif //LABORATOR_10_11_CARTAPARTMENT_H
