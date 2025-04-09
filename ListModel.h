#ifndef LABORATOR_10_11_LISTMODEL_H
#define LABORATOR_10_11_LISTMODEL_H

#include <QAbstractListModel>
#include <string>
#include <vector>

#include "domain/apartment.h"

using namespace std;

class ListModel : public QAbstractListModel {
    vector<Apartment> apartments;
    public:
        ListModel(const vector<Apartment>& apartments) : apartments{ apartments } {}

        int rowCount(const QModelIndex &parent) const override {
            return apartments.size();
        }

        int columnCount(const QModelIndex&parent = QModelIndex()) const override {
            return 4;
        }

        QVariant data(const QModelIndex &index, int role) const override {
            if (!index.isValid() || index.row() +1 >= apartments.size())
                return QVariant();

            if (role == Qt::DisplayRole) {
                Apartment a = apartments.at(index.row() + 1);
                if (index.column() == 0)
                    return QString::number(a.get_apartmentNumber());
                if (index.column() == 1)
                    return QString::fromStdString(a.get_ownerName());
                if (index.column() == 2)
                    return QString::number(a.get_surface());
                if (index.column() == 3)
                    return QString::fromStdString(a.get_apartmentType());
            }

            return QVariant();
        }

        void setApartments(const vector<Apartment>& apartments) {
            this->apartments = apartments;
            auto topLeft = createIndex(0, 0);
            int x = apartments.size();
            auto bottomRight = createIndex(x, 4);
            emit dataChanged(topLeft, bottomRight);
            emit layoutChanged();
        }
};

#endif //LABORATOR_10_11_LISTMODEL_H
