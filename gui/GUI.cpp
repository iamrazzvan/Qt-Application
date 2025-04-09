#include "GUI.h"

void GUI::initializareGUI() {
    this->setLayout(mainLayout);

    QWidget *widgetForm = new QWidget;
    QFormLayout *flForm = new QFormLayout;
    widgetForm->setLayout(flForm);
    flForm->addRow("Numar apartament", textApartmentNumber);
    flForm->addRow("Nume proprietar", textOwnerName);
    flForm->addRow("Suprafata", textSuface);
    flForm->addRow("Tip apartament", textApartmentType);
    flForm->addRow("Nume proprietar cautat", textOwnerNameCautat);

    mainLayout1->addWidget(widgetForm);

    mainLayout1->addWidget(list);

    mainLayout->addLayout(mainLayout1);

    QHBoxLayout *primaLinie = new QHBoxLayout;
    primaLinie->addWidget(butonAdaugare);
    primaLinie->addWidget(butonStergere);
    primaLinie->addWidget(butonModificare);
    primaLinie->addWidget(butonAfisare);

    QHBoxLayout *aDouaLinie = new QHBoxLayout;
    aDouaLinie->addWidget(butonUndo);

    QHBoxLayout *aTreiaLinie = new QHBoxLayout;
    aTreiaLinie->addWidget(butonFiltrareTip);
    aTreiaLinie->addWidget(butonFiltrareSuprafata);

    QHBoxLayout *aPatraLinie = new QHBoxLayout;
    aPatraLinie->addWidget(butonSortareNume);
    aPatraLinie->addWidget(butonSortareSuprafata);
    aPatraLinie->addWidget(butonSortareTipSuprafata);

    mainLayout->addLayout(primaLinie);
    mainLayout->addLayout(aDouaLinie);
    mainLayout->addLayout(aTreiaLinie);
    mainLayout->addLayout(aPatraLinie);
    mainLayout->addWidget(butonCos);
    mainLayout->addWidget(butonCosRO);
    mainLayout->addWidget(butonExit);

    QFormLayout *flForm1 = new QFormLayout;
    flForm1->addRow(new QLabel("Nume proprietar"), textOwnerNameCos);
    flForm1->addRow(new QLabel("Numar apartamente"), textNumberCos);
    flForm1->addRow(new QLabel("Fisier"), textFileCos);

    mainLayout->addLayout(flForm1);
    mainLayout->addWidget(butonGolireCos);
    mainLayout->addWidget(butonAdaugareCos);
    mainLayout->addWidget(butonAdaugareCosN);
    mainLayout->addWidget(butonExportCos);

    afisareApartamente(service.getRepoApartment(), list);

    this->afisareTipuri();

    mainLayout->addLayout(linieButoaneMap);

    qlv->setModel(listModel);
    mainLayout->addWidget(qlv);
}

void GUI::afisareTipuri() {
    map = service.report();
    if (primaData == 0) {
        for (auto b: butoaneRaport) {
            linieButoaneMap->removeWidget(b);
            delete b;
        }
        butoaneRaport.clear();
    }

    primaData = 0;

    for (auto pair: map) {
        QPushButton *b = new QPushButton();
        b->setText(QString::fromStdString(pair.first));
        butoaneRaport.push_back(b);
        linieButoaneMap->addWidget(b);
        QObject::connect(b, &QPushButton::clicked, [this, b]() { this->functieButonMap(b); });
    }
}

void GUI::functieButonMap(const QPushButton *b) {
    QMessageBox *mes = new QMessageBox();
    int value = map[b->text().toStdString()];
    mes->setText(QString::fromStdString(to_string(value)));
    mes->show();
}

void afisareMesaj(string mesaj) {
    QMessageBox *mb = new QMessageBox;
    mb->setText(QString::fromStdString(mesaj));
    mb->exec();
}

void GUI::initializareConnect() {
    QPushButton::connect(butonAdaugare, &QPushButton::clicked, [this]() {
        try {
            service.addService(textApartmentNumber->text().toInt(), textOwnerName->text().toStdString(), textSuface->text().toDouble(), textApartmentType->text().toStdString());
            afisareApartamente(service.getRepoApartment(), list);
            listModel->setApartments(service.getRepoApartment());
            afisareTipuri();
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
        catch (exception e) {
            afisareMesaj(e.what());
        }
    });

    QPushButton::connect(butonStergere, &QPushButton::clicked, [this]() {
        try {
            service.deleteService(textOwnerNameCautat->text().toStdString());
            afisareApartamente(service.getRepoApartment(), list);
            listModel->setApartments(service.getRepoApartment());
            afisareTipuri();
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonModificare, &QPushButton::clicked, [this]() {
        try {
            service.modifyService(textApartmentNumber->text().toInt(), textOwnerName->text().toStdString(), textOwnerNameCautat->text().toStdString(), textSuface->text().toDouble(), textApartmentType->text().toStdString());
            afisareApartamente(service.getRepoApartment(), list);
            listModel->setApartments(service.getRepoApartment());
            afisareTipuri();
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonUndo, &QPushButton::clicked, [this]() {
        try {
            service.undo();
            listModel->setApartments(service.getRepoApartment());
            afisareApartamente(service.getRepoApartment(), list);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonAfisare, &QPushButton::clicked, [this]() {
        try {
            afisareApartamente(service.getRepoApartment(), list);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonFiltrareTip, &QPushButton::clicked, [this]() {
        afisareApartamente(service.generic_filter(1, textApartmentType->text().toStdString()), list);
    });

    QPushButton::connect(butonFiltrareSuprafata, &QPushButton::clicked, [this]() {
        afisareApartamente(service.generic_filter(2, textSuface->text().toStdString()), list);
    });

    QPushButton::connect(butonSortareNume, &QPushButton::clicked, [this]() {
        afisareApartamente(service.generic_sort(1), list);
    });

    QPushButton::connect(butonSortareSuprafata, &QPushButton::clicked, [this]() {
        afisareApartamente(service.generic_sort(2), list);
    });

    QPushButton::connect(butonSortareTipSuprafata, &QPushButton::clicked, [this]() {
        afisareApartamente(service.generic_sort(3), list);
    });

    QPushButton::connect(butonCos, &QPushButton::clicked, [this]() {
        GUICart *cos = new GUICart{ service };
        cos->show();
    });

    QPushButton::connect(butonCosRO,&QPushButton::clicked,[this](){
        GUICartReadOnly* guiCro = new GUICartReadOnly{ service };
        guiCro->show();
    });

    QPushButton::connect(butonAdaugareCos, &QPushButton::clicked, [this]() {
        try {
            this->service.addToCartService(textOwnerNameCos->text().toStdString());
            afisareApartamente(service.getRepoApartment(), listCos);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonAdaugareCosN, &QPushButton::clicked, [this]() {
        try {
            this->service.addRandomToCartService(textNumberCos->text().toInt());
            afisareApartamente(service.getRepoApartment(), listCos);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonGolireCos, &QPushButton::clicked, [this]() {
        try {
            this->service.emptyCartService();
            afisareApartamente(service.getRepoApartment(), listCos);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonExportCos, &QPushButton::clicked, [this]() {
        try {
            this->service.saveCartToFileService(textFileCos->text().toStdString());
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonAfisareCos, &QPushButton::clicked, [this]() {
        try {
            afisareApartamente(service.getCartApartment(), listCos);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });
}

string formatApartment(Apartment apartment) {
    return "Numar: " + to_string(apartment.get_apartmentNumber()) + " Nume: " + apartment.get_ownerName() + " Suprafata: " + to_string(apartment.get_surface()) + " Tip: " + apartment.get_apartmentType();
}

void GUI::afisareApartamente(vector<Apartment> apartments, QListWidget *lista) {
    lista->clear();
    for (auto apartment: apartments) {
        lista->addItem(QString::fromStdString(formatApartment(apartment)));
    }
}

void GUICart::initializareGUICart() {
    this->setLayout(mainLayoutCart);

    service.cartApartment.addObserver(this);

    QFormLayout *flForm = new QFormLayout;
    flForm->addRow(new QLabel("Nume proprietar"), textOwnerNameCart);
    flForm->addRow(new QLabel("Numar apartamente"), textNumberCart);
    flForm->addRow(new QLabel("Fisier"), textFileCart);

    mainLayoutCart->addLayout(flForm);
    mainLayoutCart->addWidget(listCart);
    mainLayoutCart->addWidget(butonAdaugareCos);
    mainLayoutCart->addWidget(butonAdaugareCosN);
    mainLayoutCart->addWidget(butonGolireCos);
    mainLayoutCart->addWidget(butonExportCos);

    this->afisareApartamente(service.getCartApartment(), listCart);
}

void GUICart::init_conn() {
    QPushButton::connect(butonAdaugareCos, &QPushButton::clicked, [this]() {
        try {
            this->service.addToCartService(textOwnerNameCart->text().toStdString());
            afisareApartamente(service.getCartApartment(), listCart);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonAdaugareCosN, &QPushButton::clicked, [this]() {
        try {
            this->service.addRandomToCartService(textNumberCart->text().toInt());
            afisareApartamente(service.getCartApartment(), listCart);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonGolireCos, &QPushButton::clicked, [this]() {
        try {
            this->service.emptyCartService();
            afisareApartamente(service.getCartApartment(), listCart);
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });

    QPushButton::connect(butonExportCos, &QPushButton::clicked, [this]() {
        try {
            this->service.saveCartToFileService(textFileCart->text().toStdString());
        }
        catch (Exceptie &e) {
            afisareMesaj(e.getMessage());
        }
    });
}

void GUICart::afisareApartamente(vector<Apartment> apartments, QListWidget *lista) {
    lista->clear();
    for (auto apartment: apartments) {
        lista->addItem(QString::fromStdString(formatApartment(apartment)));
    }
}