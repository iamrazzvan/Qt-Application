#ifndef LABORATOR_10_11_REPOAPARTMENT_H
#define LABORATOR_10_11_REPOAPARTMENT_H

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "../domain/apartment.h"

using namespace std;

class RepoAbstract {
public:
    vector <Apartment> vectorApartment;
    virtual void addApartmentRepo(Apartment& apartment) = 0;
    virtual void deleteApartmentRepo(string ownerName) = 0;
    virtual void updateApartmentRepo(string ownerName, const Apartment& apartment) = 0;
    virtual Apartment getApartmentIndex(int index) = 0;
    virtual vector<Apartment> getApartmentList() = 0;
    virtual int getLengthRepo() noexcept = 0;
    virtual ~RepoAbstract() = default;
};

class RepoApartmentWithoutFile :public RepoAbstract
{
private:
    int length = 0;

public:
    RepoApartmentWithoutFile() = default;

    void addApartmentRepo(Apartment& apartment) override;

    void deleteApartmentRepo(string ownerName) override;

    void updateApartmentRepo(string ownerName, const Apartment& apartment) override;

    Apartment getApartmentIndex(int index) override;

    vector<Apartment> getApartmentList() override;

    int getLengthRepo() noexcept override;
};

class RepoApartmentWithFile : public RepoAbstract {
private:
    int lenght = 0;
    string fileName;

public:
    RepoApartmentWithFile() = default;

    RepoApartmentWithFile(string fileName) : fileName{fileName} {
        this->loadFromFile();
    }

    void loadFromFile();

    void writeToFile();

    void addApartmentRepo(Apartment& apartment) override;

    void deleteApartmentRepo(string ownerName) override;

    void updateApartmentRepo(string ownerName, const Apartment& apartment) override;

    Apartment getApartmentIndex(int index) override;

    vector<Apartment> getApartmentList() override;

    int getLengthRepo() noexcept override;
};

#endif //LABORATOR_10_11_REPOAPARTMENT_H
