#ifndef LABORATOR_10_11_GUI_H
#define LABORATOR_10_11_GUI_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QCoreApplication>
#include <unordered_map>
#include <QPainter>
#include <random>
#include <QListView>
#include <QTableView>

#include "../exceptions/excepApartment.h"
#include "../ListModel.h"
#include "../Observer.h"
#include "../service/srvApartment.h"

using namespace std;

class GUICart : public QWidget, public Observer {
    SrvApartment& service;

    QVBoxLayout* mainLayoutCart = new QVBoxLayout;

    QLineEdit *textOwnerNameCart = new QLineEdit;
    QLineEdit *textNumberCart = new QLineEdit;
    QLineEdit *textFileCart = new QLineEdit;

    QListWidget *listCart = new QListWidget;

    QPushButton *butonAdaugareCos = new QPushButton("Adaugare la cos");
    QPushButton *butonAdaugareCosN = new QPushButton("Adaugare n apartamente la cos");
    QPushButton *butonGolireCos = new QPushButton("Golire cos");
    QPushButton *butonExportCos = new QPushButton("Salvati cosul in fisier");
    QPushButton *butonAfisareCos = new QPushButton("Afisati continutul cosului");

    public:
        GUICart(SrvApartment& service) : service{ service } {
            initializareGUICart();
            init_conn();
        }

        void initializareGUICart();

        void init_conn();

        void update() override {
            this->afisareApartamente(service.getCartApartment(), listCart);
        }

        void afisareApartamente(vector<Apartment>, QListWidget *lista);
};

class GUICartReadOnly : public QWidget, public Observer {
    SrvApartment& service;

    public:
        GUICartReadOnly(SrvApartment& service) : service{ service } {
            init_gui();
        }

        void init_gui() {
            auto lyMain = new QVBoxLayout();
            setLayout(lyMain);
            service.cartApartment.addObserver(this);
        }

        void update() override {
            repaint();
        }

        void paintEvent(QPaintEvent* ev) override {
            QPainter p{ this };
            mt19937 mt{ random_device{}() };
            uniform_int_distribution<> dist( 1, 300 );
            for (const auto& u: service.getCartApartment()) {
                int x = dist(mt);
                int y = dist(mt);
                p.drawRect(x, y, 100, 100);
            }
        }
};

class GUI : public QWidget {
    private:
        SrvApartment service;

        GUICartReadOnly* guiCR = new GUICartReadOnly{ service };

        int primaData = 1;

        unordered_map<string, int> map;
        vector<QPushButton *> butoaneRaport;
        QHBoxLayout *linieButoaneMap = new QHBoxLayout;

        ListModel* listModel = new ListModel{ service.getRepoApartment() };
        QTableView* qlv = new QTableView;

        QVBoxLayout *mainLayout = new QVBoxLayout;
        QHBoxLayout *mainLayout1 = new QHBoxLayout;
        QVBoxLayout *mainLayoutCart = new QVBoxLayout;

        QLineEdit *textApartmentNumber = new QLineEdit;
        QLineEdit *textOwnerName = new QLineEdit;
        QLineEdit *textSuface = new QLineEdit;
        QLineEdit *textApartmentType = new QLineEdit;
        QLineEdit *textOwnerNameCautat = new QLineEdit;

        QListWidget *list = new QListWidget;

        QPushButton *butonAdaugare = new QPushButton("Adaugare apartament");
        QPushButton *butonStergere = new QPushButton("Stergere apartament");
        QPushButton *butonModificare = new QPushButton("Modificare apartament");
        QPushButton *butonAfisare = new QPushButton("Afisare apartamente");
        QPushButton *butonUndo = new QPushButton("Undo");
        QPushButton *butonFiltrareTip = new QPushButton("Filtrare dupa tip");
        QPushButton *butonFiltrareSuprafata = new QPushButton("Filtrare dupa suprafata");
        QPushButton *butonSortareNume = new QPushButton("Sortare dupa numele proprietarului");
        QPushButton *butonSortareSuprafata = new QPushButton("Sortare dupa suprafata");
        QPushButton *butonSortareTipSuprafata = new QPushButton("Sortare dupa tipul apartamentului si suprafata");
        QPushButton *butonCos = new QPushButton("Cos GUI");
        QPushButton *butonCosRO = new QPushButton("Cos GUI READ ONLY");
        QPushButton *butonExit = new QPushButton("Iesire");

        QLineEdit *textOwnerNameCos = new QLineEdit;
        QLineEdit *textNumberCos = new QLineEdit;
        QLineEdit *textFileCos = new QLineEdit;

        QListWidget *listCos = new QListWidget;

        QPushButton *butonAdaugareCos = new QPushButton("Adaugare la cos");
        QPushButton *butonAdaugareCosN = new QPushButton("Adaugare n apartamente la cos");
        QPushButton *butonGolireCos = new QPushButton("Golire cos");
        QPushButton *butonExportCos = new QPushButton("Salvati cosul in fisier");
        QPushButton *butonAfisareCos = new QPushButton("Afisati continutul cosului");

        void initializareGUI();

        void initializareGUICart();

        void initializareConnect();

        void afisareTipuri();

        void functieButonMap(const QPushButton *b);

        void afisareApartamente(vector<Apartment>, QListWidget *lista);

    public:
        GUI(SrvApartment& service) : service{ service } {
            initializareGUI();
            initializareConnect();
        }
};

#endif //LABORATOR_10_11_GUI_H
