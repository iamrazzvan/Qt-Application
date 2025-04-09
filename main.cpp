#include <QApplication>

#include "gui/GUI.h"
#include "tests/tests.h"
#include "ui/console.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    testAll();
    RepoApartmentWithFile* r = new RepoApartmentWithFile("C:\\Users\\Razvan Racovita\\OneDrive\\CS-UBB_CJ\\Anul_I\\2nd semester\\OOP\\Laborator\\Laborator_10-11\\fisier.txt");
    CartApartment c;
    SrvApartment s{ r, c };
    GUI g { s };
    g.show();
    return a.exec();
}
