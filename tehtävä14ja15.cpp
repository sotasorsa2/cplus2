#include <iostream>
#include <cstdlib> // malloc, free
#include <cstring> // memcpy

class Big_Data {
public:
    // Konstruktori
    explicit Big_Data(size_t size) : buffer_size(size), buffer(nullptr) {
        buffer = static_cast<char*>(std::malloc(buffer_size));
        if (buffer == nullptr) {
            std::cerr << "Error: Failed to allocate memory." << std::endl;
        }
    }

    // Destruktori
    ~Big_Data() {
        if (buffer != nullptr) {
            std::free(buffer);
            buffer = nullptr;
        }
    }

    // Kopiokonstruktori
    Big_Data(const Big_Data& other) : buffer_size(other.buffer_size), buffer(nullptr) {
        buffer = static_cast<char*>(std::malloc(buffer_size));
        if (buffer == nullptr) {
            std::cerr << "Error: Failed to allocate memory." << std::endl;
        } else {
            std::memcpy(buffer, other.buffer, buffer_size);
        }
    }

    // Sijoitusoperaattori
    Big_Data& operator=(const Big_Data& other) {
        if (this != &other) {
            // Vapautetaan vanha muisti
            if (buffer != nullptr) {
                std::free(buffer);
            }
            // Varataan uusi muisti ja kopioidaan sisältö
            buffer_size = other.buffer_size;
            buffer = static_cast<char*>(std::malloc(buffer_size));
            if (buffer == nullptr) {
                std::cerr << "Error: Failed to allocate memory." << std::endl;
            } else {
                std::memcpy(buffer, other.buffer, buffer_size);
            }
        }
        return *this;
    }

    // Move-konstruktori
    Big_Data(Big_Data&& other) noexcept : buffer_size(other.buffer_size), buffer(other.buffer) {
        other.buffer_size = 0;
        other.buffer = nullptr;
    }

    // Move-sijoitusoperaattori
    Big_Data& operator=(Big_Data&& other) noexcept {
        if (this != &other) {
            // Vapautetaan vanha muisti
            if (buffer != nullptr) {
                std::free(buffer);
            }
            // Siirretään toisen olion muisti tähän ja nollataan toisen olion muisti
            buffer_size = other.buffer_size;
            buffer = other.buffer;
            other.buffer_size = 0;
            other.buffer = nullptr;
        }
        return *this;
    }

private:
    char* buffer;
    size_t buffer_size;
};

int main() {
    // Testataan luokan toimintaa
    Big_Data a(1024);
    Big_Data b(1024);

    // Sijoitetaan a itselleen
    a = a;

    // Sijoitetaan b a:han
    a = b;

    // Käytetään kopiokonstruktoria
    Big_Data c(a);

    // Testataan move-semantiikkaa
    Big_Data d(Big_Data(1024)); // Move-konstruktori
    Big_Data e(1024);
    e = Big_Data(1024); // Move-sijoitusoperaattori
    Big_Data f(std::move(a)); // Move-konstruktori

    return 0;
}
