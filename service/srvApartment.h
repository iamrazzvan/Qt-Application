#ifndef LABORATOR_10_11_SRVAPARTMENT_H
#define LABORATOR_10_11_SRVAPARTMENT_H

#include <algorithm>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include "../cart/cartApartment.h"
#include "../domain/apartment.h"
#include "../exceptions/excepApartment.h"
#include "../repository/repoApartment.h"
#include "../undo/undoApartment.h"

class SrvApartment {
    private:
        RepoAbstract* repoApartment;
        vector<ActionUndo*> ActiuniUndo;

    public:
        CartApartment& cartApartment;

        SrvApartment(RepoAbstract* repoApartment, CartApartment& cartApartment) noexcept : repoApartment(repoApartment), cartApartment{ cartApartment } {}

        void deleteUndo();

        void addService(int apartmentNumber, string ownerName, double surface, string apartmentType);

        void deleteService(string ownerName);

        void modifyService(int apartmentNumber, string ownerName, string ownerName1, double surface, string apartmentType);

        vector <Apartment> generic_filter(int choice, string criteriu);

        vector <Apartment> main_filter(int (*filter_func)(Apartment& apartment, string criteriu), string criteriu1);

        vector<Apartment> generic_sort(int choice);

        vector<Apartment> main_sort(int (*sort_func)(Apartment&, Apartment&));

        void addToCartService(string ownerName);

        void addRandomToCartService(int number);

        void emptyCartService();

        void saveCartToFileService(string filename);

        void undo();

        unordered_map<string, int> report();

        vector<Apartment> getRepoApartment();

        vector<Apartment> getCartApartment();
};

#endif //LABORATOR_10_11_SRVAPARTMENT_H
