#include "srvApartment.h"

void SrvApartment::addService(int apartmentNumber, string ownerName, double surface, string apartmentType) {
    Apartment apartment(apartmentNumber, ownerName, surface, apartmentType);
    Apartment::validator(apartment);
    this->repoApartment->addApartmentRepo(apartment);
    ActiuniUndo.push_back(new UndoAdd{ this->repoApartment, ownerName });
}

void SrvApartment::deleteUndo() {
    for (auto x : this->ActiuniUndo)
        delete x;
}

void SrvApartment::deleteService(string ownerName) {
    Apartment apartmentDeleted;
    vector<Apartment> v = this->repoApartment->getApartmentList();
    vector<Apartment>::iterator it = find_if(v.begin(), v.end(), [ownerName](Apartment& apartment) {
        return ownerName == apartment.get_ownerName();
    });
    if (it == v.end())
    {
        throw(Exceptie("Nu exista element cu numele dorit in lista"));
    }
    apartmentDeleted = *it;
    repoApartment->deleteApartmentRepo(ownerName);
    ActiuniUndo.push_back(new UndoDelete{ this->repoApartment , apartmentDeleted });
}

void SrvApartment::modifyService(int apartmentNumber, string ownerName, string ownerName1, double surface, string apartmentType) {
    Apartment a = Apartment(apartmentNumber, ownerName, surface, apartmentType);
    Apartment apartmentModified;
    Apartment::validator(a);
    vector<Apartment> v = this->repoApartment->getApartmentList();
    vector<Apartment>::iterator it = find_if(v.begin(), v.end(), [ownerName1](Apartment& apartment) {
        return ownerName1 == apartment.get_ownerName();
    });
    if (it == v.end())
    {
        throw(Exceptie("Nu exista element cu numele dorit in lista"));
    }
    apartmentModified = *it;
    repoApartment->updateApartmentRepo(ownerName1, a);
    ActiuniUndo.push_back(new UndoModify{ this->repoApartment , apartmentModified, ownerName });
}

void SrvApartment::undo() { if (ActiuniUndo.size() == 0) throw Exceptie("Nu mai exista operatii de undo"); ActionUndo* actiune = ActiuniUndo.back(); actiune->doUndo(); ActiuniUndo.pop_back(); delete actiune; }

int sort_ownerName(Apartment& a1, Apartment& a2) {
    if (a1.get_ownerName() < a2.get_ownerName()) { return 1; }
    return 0;
}

int sort_surface(Apartment& a1, Apartment& a2) {
    if (a1.get_surface() < a2.get_surface()) { return 1; }
    return 0;
}

int sort_apartmentTypeandSurface(Apartment& a1, Apartment& a2) {
    if (a1.get_apartmentType() < a2.get_apartmentType()) { return 1; }
    else if (a1.get_apartmentType() == a2.get_apartmentType()) {
        if (a1.get_surface() < a2.get_surface()) return 1;
        return 0;
    }
    return 0;
}

int filter_apartmentType(Apartment& a, string apartmentType) {
    if (a.get_apartmentType() == apartmentType)
        return 1;
    return 0;
}

int filter_surface(Apartment& a, string surface) {
    if (a.get_surface() == stod(surface))
        return 1;
    return 0;
}

vector <Apartment> SrvApartment::generic_filter(int choice, string criteriu) {
    vector<Apartment> gol;
    if (choice == 1)
        return main_filter(filter_apartmentType, criteriu);
    if (choice == 2)
        return main_filter(filter_surface, criteriu); return gol;
}

vector <Apartment> SrvApartment::main_filter(int (*filter_func)(Apartment& apartment, string criteriu), string criteriu1) {
    vector<Apartment> v = this->repoApartment->getApartmentList();
    vector<Apartment> filtered_list(v.size());
    auto it = copy_if(v.begin(), v.end(), filtered_list.begin(), [filter_func, criteriu1](Apartment& apartment) {
        return filter_func(apartment, criteriu1);
    });
    filtered_list.resize(distance(filtered_list.begin(), it));
    return filtered_list;
}

vector<Apartment> SrvApartment::generic_sort(int choice) {
    vector<Apartment> gol;
    if (choice == 1)
        return main_sort(sort_ownerName);
    if (choice == 2)
        return main_sort(sort_surface);
    if (choice == 3)
        return main_sort(sort_apartmentTypeandSurface); return gol;
}

vector<Apartment> SrvApartment::main_sort(int (*sort_func)(Apartment&, Apartment&)) {
    vector<Apartment> v = this->getRepoApartment();
    sort(v.begin(), v.end(), sort_func);
    return v; }

void SrvApartment::addToCartService(string ownerName) {
    Apartment apartmentFound;
    vector<Apartment> v = this->repoApartment->getApartmentList();
    vector<Apartment>::iterator it = find_if(v.begin(), v.end(), [ownerName](Apartment& apartment) {
        return ownerName == apartment.get_ownerName();
    });
    if (it == v.end()) { throw(Exceptie("Nu exista element cu numele dorit in lista")); }
    int pos = (int)(it - v.begin());
    apartmentFound = v[pos];
    cartApartment.addApartmentToCart(apartmentFound);
}

void SrvApartment::addRandomToCartService(int number) {
    vector<Apartment> v = this->getRepoApartment();
    while (v.size() != 0 && number > 0 ) {
        std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<> dist(0, (int)(v.size() - 1));
        int rndNr = dist(mt);
        Apartment apartment = v[rndNr];
        v.erase(v.begin()+rndNr);
        cartApartment.addApartmentToCart(apartment);
        number--;
    }
}

void SrvApartment::emptyCartService() {
    this->cartApartment.emptyCart();
}

void SrvApartment::saveCartToFileService(string filename) { this->cartApartment.exportCart(filename); }

unordered_map<string, int> SrvApartment::report() {
    unordered_map<string, int> report;
    vector<Apartment> v = this->repoApartment->getApartmentList();
    for (auto x : v) {
        int ok = 0;
        for (auto& str: report) {
            if (str.first == x.get_apartmentType()) {
                str.second++;
                ok = 1;
                break;
            }
        }
        if (ok == 0) {
            report[x.get_apartmentType()] = 1;
        }
    }
    return report;
}

vector<Apartment> SrvApartment::getRepoApartment() {
    return this->repoApartment->getApartmentList();
}

vector<Apartment> SrvApartment::getCartApartment() {
    return this->cartApartment.getCart();
}