#include "tests.h"

void test_classApartment() {
    Apartment a1 = Apartment(1, "Owner1", 100, "decomandat");
    Apartment a2;
    a2 = a1;

    a2.set_apartmentNumber(2);
    a2.set_ownerName("Owner2");
    a2.set_surface(200);
    a2.set_apartmentType("nedecomandat");

    assert(a1.get_apartmentNumber() != a2.get_apartmentNumber());
    assert(a1.get_ownerName() != a2.get_ownerName());
    assert(a1.get_surface() != a2.get_surface());
    assert(a1.get_apartmentType() != a2.get_apartmentType());

    a1 = Apartment(0, "", 0, "");
    try {
        Apartment::validator(a1);
        assert(false);
    } catch (ExceptieValidator e) {
        assert(true);
    }
    Apartment::validator(a2);
    Apartment a3 = Apartment(-1, "Owner3", -300, "semidecomandat");
    try {
        Apartment::validator(a3);
        assert(false);
    } catch (ExceptieValidator e) {
        assert(true);
    }
}

void test_classRepo() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    Apartment a1 = Apartment(1, "Owner1", 100, "decomandat");
    Apartment a2 = Apartment(2, "Owner2", 200, "nedecomandat");
    repo->addApartmentRepo(a1);
    assert(repo->getApartmentList().size() == 1);
    string s1 = "Owner1";
    repo->updateApartmentRepo(s1, a2);
    assert(repo->getApartmentList()[0].get_ownerName() == a2.get_ownerName());
    repo->deleteApartmentRepo("Owner2");
    assert(repo->getApartmentList().size() == 0);
    vector<Apartment> v = repo->getApartmentList();
    delete repo;
}

void test_classCart() {
    CartApartment cart;
    Apartment a1 = Apartment(1, "Owner1", 100, "decomandat");
    Apartment a2 = Apartment(2, "Owner2", 200, "nedecomandat");
    cart.addApartmentToCart(a1);
    cart.addApartmentToCart(a2);
    assert(cart.getCart().size() == 2);
    cart.emptyCart();
    assert(cart.getCart().size() == 0);
    vector<Apartment> v = cart.getCart();
}

void test_filter() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment service{ repo, cart };

    service.addService(1, "Owner1", 100, "decomandat");
    service.addService(2, "Owner2", 200, "decomandat");
    service.addService(3, "Owner3", 300, "semidecomandat");

    vector<Apartment> v = service.generic_filter(1, "decomandat");
    assert(v[0].get_apartmentType() == "decomandat");
    assert(v[0].get_ownerName() == "Owner1");
    assert(v[1].get_apartmentType() == "decomandat");
    assert(v[1].get_ownerName() == "Owner2");

    v = service.generic_filter(2, "200");
    assert(v[0].get_surface() == 200);
    assert(v[0].get_ownerName() == "Owner2");

    service.deleteUndo();
    delete repo;
}

void test_sort() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment service{ repo, cart };

    service.addService(1, "Owner1", 100, "decomandat");
    service.addService(2, "Owner2", 200, "decomandat");
    service.addService(3, "Owner3", 300, "semidecomandat");

    vector<Apartment> v = service.generic_sort(1);
    assert(v[0].get_ownerName() == "Owner1");

    v = service.generic_sort(2);
    assert(v[0].get_surface() == 100);

    v = service.generic_sort(3);
    assert(v[0].get_apartmentType() == "decomandat");
    assert(v[0].get_surface() == 100);

    service.deleteUndo();
    delete repo;
}

void test_file() {
    RepoAbstract* repo = new RepoApartmentWithFile("C:\\Users\\Razvan Racovita\\OneDrive\\CS-UBB_CJ\\Anul_I\\2nd semester\\OOP\\Laborator\\Laborator_10-11\\fisier.txt");
    assert(repo->getApartmentList().size() == 5);
    Apartment a(4, "Owner4", 400, "nedecomandat");
    repo->addApartmentRepo(a);
    repo->deleteApartmentRepo("Owner4");
    delete repo;
}

void test_addApartmentRepo() {
    RepoApartmentWithoutFile repo;
    Apartment apt(1, "Owner1", 100, "decomandat");
    repo.addApartmentRepo(apt);
    assert(repo.getLengthRepo() == 1);
    assert(repo.getApartmentIndex(0).get_apartmentNumber() == 1);
    assert(repo.getApartmentIndex(0).get_ownerName() == "Owner1");
    assert(repo.getApartmentIndex(0).get_surface() == 100);
    assert(repo.getApartmentIndex(0).get_apartmentType() == "decomandat");
}

void test_deleteApartmentRepo() {
    RepoApartmentWithoutFile repo;
    Apartment apt1(1, "Owner1", 100, "decomandat");
    Apartment apt2(2, "Owner2", 200, "nedecomandat");
    repo.addApartmentRepo(apt1);
    repo.addApartmentRepo(apt2);
    assert(repo.getLengthRepo() == 2);
    repo.deleteApartmentRepo("Owner1");
    assert(repo.getLengthRepo() == 1);
    assert(repo.getApartmentIndex(0).get_ownerName() != "Owner1");
}

void test_updateApartmentRepo() {
    RepoApartmentWithoutFile repo;
    Apartment apt1(1, "Owner1", 100, "decomandat");
    Apartment apt2(2, "Owner2", 200, "nedecomandat");
    repo.addApartmentRepo(apt1);
    repo.addApartmentRepo(apt2);
    assert(repo.getLengthRepo() == 2);
    Apartment aptUpdated(1, "Owner1", 150, "decomandat");
    repo.updateApartmentRepo("Owner1", aptUpdated);
    assert(repo.getApartmentIndex(0).get_surface() == 150);
}

void test_getApartmentList() {
    RepoApartmentWithoutFile repo;
    Apartment apt1(1, "Owner1", 100, "decomandat");
    Apartment apt2(2, "Owner2", 200, "nedecomandat");
    repo.addApartmentRepo(apt1);
    repo.addApartmentRepo(apt2);
    vector<Apartment> apartments = repo.getApartmentList();
    assert(apartments.size() == 2);
    assert(apartments[0].get_ownerName() == "Owner1");
    assert(apartments[1].get_ownerName() == "Owner2");
}

void test_getApartmentIndex() {
    RepoApartmentWithFile repo;
    Apartment apt1(1, "Owner1", 100, "decomandat");
    Apartment apt2(2, "Owner2", 200, "nedecomandat");
    repo.addApartmentRepo(apt1);
    repo.addApartmentRepo(apt2);
    Apartment apt = repo.getApartmentIndex(0);
    assert(apt.get_apartmentNumber() == 1);
    assert(apt.get_ownerName() == "Owner1");
    assert(apt.get_surface() == 100);
    assert(apt.get_apartmentType() == "decomandat");
}

void test_getLengthRepo() {
    RepoApartmentWithFile repo;
    Apartment apt1(1, "Owner1", 100, "decomandat");
    Apartment apt2(2, "Owner2", 200, "nedecomandat");
    repo.addApartmentRepo(apt1);
    repo.addApartmentRepo(apt2);
    assert(repo.getLengthRepo() == 2);
}

void testDeleteService() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment srv { repo, cart };
    string ownerName = "TestOwner";

    // Add an apartment to the service
    srv.addService(1, ownerName, 100.0, "TestType");

    // Ensure the apartment was added
    vector<Apartment> apartments = srv.getRepoApartment();
    assert(apartments.size() == 1);
    assert(apartments[0].get_ownerName() == ownerName);

    // Delete the apartment
    srv.deleteService(ownerName);

    // Ensure the apartment was deleted
    apartments = srv.getRepoApartment();
    assert(apartments.size() == 0);

    // Ensure an exception is thrown when trying to delete a non-existent apartment
    bool exceptionThrown = false;
    try {
        srv.deleteService(ownerName);
    } catch (const Exceptie& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void testModifyService() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment srvApartment { repo, cart };
    string ownerName = "TestOwner";
    string newOwnerName = "NewTestOwner";
    double surface = 100.0;
    string apartmentType = "TestType";
    int apartmentNumber = 1;

    // Add an apartment to the service
    srvApartment.addService(apartmentNumber, ownerName, surface, apartmentType);

    // Ensure the apartment was added
    vector<Apartment> apartments = srvApartment.getRepoApartment();
    assert(apartments.size() == 1);
    assert(apartments[0].get_ownerName() == ownerName);

    // Modify the apartment
    srvApartment.modifyService(apartmentNumber, newOwnerName, ownerName, surface, apartmentType);

    // Ensure the apartment was modified
    apartments = srvApartment.getRepoApartment();
    assert(apartments.size() == 1);
    assert(apartments[0].get_ownerName() == newOwnerName);

    // Ensure an exception is thrown when trying to modify a non-existent apartment
    bool exceptionThrown = false;
    try {
        srvApartment.modifyService(apartmentNumber, "NonExistentOwner", ownerName, surface, apartmentType);
    } catch (const Exceptie& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void testAddRandomToCartService() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment srv { repo, cart };

    // Add apartments to the service
    srv.addService(1, "Owner1", 100.0, "Type1");
    srv.addService(2, "Owner2", 200.0, "Type1");
    srv.addService(3, "Owner3", 300.0, "Type2");

    // Add a random apartment to the cart
    srv.addRandomToCartService(1);

    // Ensure an apartment was added to the cart
    vector<Apartment> apartmentsInCart = srv.getCartApartment();
    assert(apartmentsInCart.size() == 1);
}

void testEmptyCartService() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment srv { repo, cart };
    string ownerName = "TestOwner";

    // Add an apartment to the service
    srv.addService(1, ownerName, 100.0, "TestType");

    // Add the apartment to the cart
    srv.addToCartService(ownerName);

    // Ensure the apartment was added to the cart
    vector<Apartment> apartmentsInCart = srv.getCartApartment();
    assert(apartmentsInCart.size() == 1);

    // Empty the cart
    srv.emptyCartService();

    // Ensure the cart is empty
    apartmentsInCart = srv.getCartApartment();
    assert(apartmentsInCart.size() == 0);
}

void testReport() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment srv { repo, cart };

    // Add apartments to the service
    srv.addService(1, "Owner1", 100.0, "Type1");
    srv.addService(2, "Owner2", 200.0, "Type1");
    srv.addService(3, "Owner3", 300.0, "Type2");

    // Generate the report
    unordered_map<string, int> report = srv.report();

    // Ensure the report is correct
    assert(report["Type1"] == 2);
    assert(report["Type2"] == 1);
}

void testGetCartApartment() {
    RepoAbstract* repo = new RepoApartmentWithFile();
    CartApartment cart;
    SrvApartment srv { repo, cart };
    string ownerName = "TestOwner";

    // Add an apartment to the service
    srv.addService(1, ownerName, 100.0, "TestType");

    // Add the apartment to the cart
    srv.addToCartService(ownerName);

    // Ensure the apartment was added to the cart
    vector<Apartment> apartmentsInCart = srv.getCartApartment();
    assert(apartmentsInCart.size() == 1);
    assert(apartmentsInCart[0].get_ownerName() == ownerName);
}

void testExportCart() {
    CartApartment cart;

    // Add an apartment to the cart
    Apartment apartment(1, "TestOwner", 100.0, "TestType");
    cart.addApartmentToCart(apartment);

    // Export the cart to a file
    string filename = "testCart";
    cart.exportCart(filename);

    // Open the file and check its contents
    ifstream file(filename + ".csv");
    string line;
    getline(file, line);

    // The line should contain the details of the apartment
    assert(line.find("1") != string::npos);
    assert(line.find("TestOwner") != string::npos);
    assert(line.find("100.0") != string::npos);
    assert(line.find("TestType") != string::npos);

    file.close();

    // Delete the test file after the test
    remove((filename + ".csv").c_str());
}

void testAll() {
    test_classApartment();
    test_classRepo();
    test_classCart();
    test_filter();
    test_sort();
    test_file();
    test_addApartmentRepo();
    test_deleteApartmentRepo();
    test_updateApartmentRepo();
    test_getApartmentList();
    test_getApartmentIndex();
    test_getLengthRepo();
    testDeleteService();
    testModifyService();
    testAddRandomToCartService();
    testEmptyCartService();
    testReport();
    testGetCartApartment();
    testExportCart();

    cout << "All tests passed!\n";
}