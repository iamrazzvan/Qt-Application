#include "repoApartment.h"

void RepoApartmentWithoutFile::addApartmentRepo(Apartment& apartment) {
    this->vectorApartment.push_back(apartment);
    this->length++;
}

void RepoApartmentWithoutFile::deleteApartmentRepo(string ownerName) {
    auto r = remove_if(this->vectorApartment.begin(), this->vectorApartment.end(), [ownerName](Apartment& apartment) {
        return ownerName == apartment.get_ownerName();
    });
    this->vectorApartment.erase(r, this->vectorApartment.end());
    this->length--;
}

void RepoApartmentWithoutFile::updateApartmentRepo(string ownerName, const Apartment& apartment) {
    replace_if(this->vectorApartment.begin(), this->vectorApartment.end(), [ownerName](Apartment& apartment) {
        return ownerName == apartment.get_ownerName();
    }, apartment);
}

Apartment RepoApartmentWithoutFile::getApartmentIndex(int index) {
    return this->vectorApartment.at(index);
}

vector<Apartment> RepoApartmentWithoutFile::getApartmentList() {
    return this->vectorApartment;
}

int RepoApartmentWithoutFile::getLengthRepo() noexcept {
    return this->length;
}

void RepoApartmentWithFile::loadFromFile() {
    ifstream file(this->fileName);
    int apartmentNumber;
    string ownerName, apartmentType;
    double surface;

    while(file >> apartmentNumber >> ownerName >> surface >> apartmentType) {
        Apartment apt{apartmentNumber, ownerName, surface, apartmentType};
        this->addApartmentRepo(apt);
    }
}

void RepoApartmentWithFile::writeToFile() {
    string text;
    for (auto apt : this->vectorApartment) {
        text += to_string(apt.get_apartmentNumber()) + " " + apt.get_ownerName() + " " + to_string(apt.get_surface()) + " " + apt.get_apartmentType() + "\n";
    }
    ofstream file(this->fileName);
    file << text;
}

void RepoApartmentWithFile::addApartmentRepo(Apartment& apartment) {
    this->vectorApartment.push_back(apartment);
    this->lenght++;
    writeToFile();
}

void RepoApartmentWithFile::deleteApartmentRepo(string ownerName) {
    auto r = remove_if(this->vectorApartment.begin(), this->vectorApartment.end(), [ownerName](Apartment& apartment) {
        return ownerName == apartment.get_ownerName();
    });
    this->vectorApartment.erase(r, this->vectorApartment.end());
    this->lenght--;
    writeToFile();
}

void RepoApartmentWithFile::updateApartmentRepo(string ownerName, const Apartment& apartment) {
    replace_if(this->vectorApartment.begin(), this->vectorApartment.end(), [ownerName](Apartment& apartment) {
        return ownerName == apartment.get_ownerName();
    }, apartment);
    writeToFile();
}

Apartment RepoApartmentWithFile::getApartmentIndex(int index) {
    return this->vectorApartment.at(index);
}

vector<Apartment> RepoApartmentWithFile::getApartmentList() {
    return this->vectorApartment;
}

int RepoApartmentWithFile::getLengthRepo() noexcept {
    return this->lenght;
}