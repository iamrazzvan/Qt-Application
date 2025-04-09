#include "console.h"

static void format(Apartment apartment) {
    cout << "Apartment number: " << apartment.get_apartmentNumber() << " | Owner Name: " << apartment.get_ownerName() << " | Surface: " << apartment.get_surface() << " | Apartment Type: " << apartment.get_apartmentType() << "\n";
}

void Console::run() {
    while (true) {
        try {
            cout << "\n\n1. Adauga apartament\n2. Sterge apartament\n3.Modifica apartament\n4. Undo\n5. Filtrare apartamente\n6. Sortare apartamente\n7. Afisare apartamente\n8. Adauga apartament in cos\n9. Adauga n apartamente in cos\n10. Golire cos\n11. Afisare cos\n12. Salvare cos\n13. Raport cu map\n0. Iesirre\n";
            cout.clear();
            int option;
            if (!(cin >> option)) {
                cin.clear();
                cin.ignore();
                cout << "Introduceti doar numere!\n";
                continue;
            }

            switch (option) {
                case 1: {
                    int apartmentNumber;
                    string ownerName;
                    double surface;
                    string apartmentType;
                    cin.get();
                    cout << "Introduceti numarul apartamentului: \n";
                    if (!(cin >> apartmentNumber)) {
                        cin.clear();
                        cin.ignore();
                        cout << "Introduceti doar numere!\n";
                        continue;
                    }

                    cin.get();
                    cout << "Introduceti numele proprietarului: \n";
                    getline(cin, ownerName);

                    cout << "Introduceti suprafata apartamentului: \n";
                    if (!(cin >> surface)) {
                        cin.clear();
                        cin.ignore();
                        cout << "Introduceti doar numere!\n";
                        continue;
                    }

                    cin.get();
                    cout << "Introduceti tipul apartamentului: \n";
                    getline(cin, apartmentType);

                    try {
                        service.addService(apartmentNumber, ownerName, surface, apartmentType);
                    }
                    catch (exception ex) {
                        cout << ex.what();
                        continue;
                    }
                    break;
                }

                case 2: {
                    string ownerName;
                    cin.get();
                    cout << "Introduceti numele proprietarului apartamentului pe care doriti sa il stergeti:\n";
                    getline(cin, ownerName);

                    try {
                        service.deleteService(ownerName);
                        cout << "Apartament sters cu succes!\n";
                    }
                    catch (exception ex) {
                        cout << ex.what();
                        continue;
                    }
                    break;
                }

                case 3: {
                    int apartmentNumber;
                    string ownerName;
                    string ownerNameNew;
                    double surface;
                    string apartmentType;
                    cin.get();
                    cout << "Introduceti numarul apartamentului pe care doriti sa il modificati: \n";
                    if (!(cin >> apartmentNumber)) {
                        cin.clear();
                        cin.ignore();
                        cout << "Introduceti doar numere!\n";
                        continue;
                    }

                    cin.get();
                    cout << "Introduceti numele proprietarului: \n";
                    getline(cin, ownerName);

                    cout << "Introduceti suprafata apartamentului: \n";
                    if (!(cin >> surface)) {
                        cin.clear();
                        cin.ignore();
                        cout << "Introduceti doar numere!\n";
                        continue;
                    }

                    cin.get();
                    cout << "Introduceti tipul apartamentului: \n";
                    getline(cin, apartmentType);

                    try {
                        service.modifyService(apartmentNumber, ownerName, ownerNameNew, surface, apartmentType);
                    }
                    catch (exception ex) {
                        cout << ex.what();
                        continue;
                    }
                    break;
                }

                case 4: {
                    service.undo();
                    break;
                }

                case 5: {
                    cout << "1. Filtrare dupa tip\n2. Filtrare dupa suprafata\n3. Iesire\n";
                    int sub_option;
                    if (!(cin >> sub_option)) {
                        cin.clear();
                        cin.ignore();
                        cout << "Introduceti doar numere!\n";
                        continue;
                    }
                    switch (sub_option) {
                        case 1: {
                            string criteriu;
                            cin.get();
                            cout << "Introduceti tipul apartamentului dupa care doriti sa filtrati:\n";
                            getline(cin, criteriu);

                            vector<Apartment> v = service.generic_filter(sub_option, criteriu);
                            int p = (int)(v.size());
                            for (int i = 0; i < p; i++) {
                                format(v[i]);
                            }
                            break;
                        }
                        case 2: {
                            string criteriu;
                            cin.get();
                            cout << "Introduceti suprafata apartamentului dupa care doriti sa filtrati:\n";
                            getline(cin, criteriu);

                            vector<Apartment> v = service.generic_filter(sub_option, criteriu);
                            int p = (int) (v.size());
                            for (int i = 0; i < p; i++) {
                                format(v[i]);
                            }
                            break;
                        }
                        case 3: {
                            break;
                        }
                            break;
                    }

                    case 6: {
                        cout << "1. Sortare dupa nume\n2. Sortare dupa suprafata\n3. Sortare dupa tip si suprafata\n4. Iesire\n";
                        int sub_option;
                        if (!(cin >> sub_option)) {
                            cin.clear();
                            cin.ignore();
                            cout << "Introduceti doar numere!\n";
                            continue;
                        }

                        switch (sub_option) {
                            case 1: {
                                vector<Apartment> v = service.generic_sort(sub_option);
                                int p = (int)(v.size());
                                for (int i = 0; i < p; i++) {
                                    format(v[i]);
                                }
                                break;
                            }
                            case 2: {
                                vector<Apartment> v = service.generic_sort(sub_option);
                                int p = (int)(v.size());
                                for (int i = 0; i < p; i++) {
                                    format(v[i]);
                                }
                                break;
                            }
                            case 3: {
                                vector<Apartment> v = service.generic_sort(sub_option);
                                int p = (int)(v.size());
                                for (int i = 0; i < p; i++) {
                                    format(v[i]);
                                }
                                break;
                            }
                            case 4: {
                                break;
                            }
                        }
                        break;
                    }

                    case 7: {
                        const size_t size = service.getRepoApartment().size();
                        if (!size) {
                            cout << "Lista este goala!\n";
                            break;
                        }
                        for (int i = 0; i < size; i++) {
                            Apartment apartment = service.getRepoApartment()[i];
                            format(apartment);
                        }
                        break;
                    }

                    case 8: {
                        string ownerName;
                        cout << "Introduceti numele proprietarului apartamentului pe care doriti sa il adaugati in cos:\n";
                        cin >> ownerName;
                        this->service.addToCartService(ownerName);
                        break;
                    }

                    case 9: {
                        int nr;
                        cout << "Introduceti numarul de apartamente pe care doriti sa le adaugati in cos:\n";
                        if (!(cin >> nr)) {
                            cin.clear();
                            cin.ignore();
                            cout << "Introduceti doar numere!\n";
                            continue;
                        }
                        this->service.addRandomToCartService(nr);
                        break;
                    }

                    case 10: {
                        this->service.emptyCartService();
                        break;
                    }

                    case 11: {
                        vector<Apartment> v = this->service.getCartApartment();
                        int p = (int)(v.size());
                        for (int i = 0; i < p; i++) {
                            format(v[i]);
                        }
                        break;
                    }

                    case 12: {
                        string fileName;
                        cout << "Introduceti numele fisierului in care doriti sa salvati cosul:\n";
                        cin >> fileName;
                        this->service.saveCartToFileService(fileName);
                        cout << "Cos salvat cu succes!\n";
                        break;
                    }

                    case 13: {
                        unordered_map<string, int> report = this->service.report();
                        for (auto x : report) {
                            cout << x.first << " - " << to_string(x.second) << "\n";
                        }
                        break;

                    }

                    case 0: {
                        this->service.deleteUndo();
                        exit(0);
                    }
                }
            }
        }
        catch (Exceptie e) {
            cout << e.getMessage();
        }
    }
}