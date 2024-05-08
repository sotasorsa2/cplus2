#include <iostream>
#include <new> // std::bad_alloc

int main() {
    try {
        // Yritetään varata valtava määrä muistia
        size_t size = 1000000000000; // Esimerkiksi varataan 1 teratavu muistia
        int* arr = new int[size];
        // Jos muistinvaraus onnistui, tulostetaan viesti
        std::cout << "Muistinvaraus onnistui!" << std::endl;

        delete[] arr;
    } catch (const std::bad_alloc& e) {
        // Jos muistinvaraus epäonnistui, tulostetaan virheviesti
        std::cerr << "Muistinvaraus epäonnistui: " << e.what() << std::endl;
    }

    return 0;
}
