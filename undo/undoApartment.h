#ifndef LABORATOR_10_11_UNDOAPARTMENT_H
#define LABORATOR_10_11_UNDOAPARTMENT_H

#include <iostream>

#include "../domain/apartment.h"
#include "../repository/repoApartment.h"

class ActionUndo {
public:
    virtual void doUndo() = 0;
    virtual ~ActionUndo() = default;
};

class UndoAdd : public ActionUndo {
private:
    string ownerName;
    RepoAbstract* repo;
public:
    UndoAdd(RepoAbstract* rep, string ownerName) : repo{ rep }, ownerName{ ownerName } {}
    void doUndo() override {
        repo->deleteApartmentRepo(ownerName);
    }
};

class UndoDelete : public ActionUndo {
private:
    Apartment apartmentDeleted;
    RepoAbstract* repo;
public:
    UndoDelete(RepoAbstract* rep, Apartment& apartment) : repo{ rep }, apartmentDeleted{ apartment } {}
    void doUndo() override {
        repo->addApartmentRepo(apartmentDeleted);
    }
};

class UndoModify : public ActionUndo {
private:
    string ownerName;
    Apartment apartmentModified;
    RepoAbstract* repo;
public:
    UndoModify(RepoAbstract* rep, Apartment& apartment, string ownerName) : repo{ rep }, apartmentModified{ apartment }, ownerName{ ownerName } {}
    void doUndo() override {
        repo->updateApartmentRepo(ownerName, apartmentModified);
    }
};

#endif //LABORATOR_10_11_UNDOAPARTMENT_H
