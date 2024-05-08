#include <iostream>
#include <memory>
#include <ctime>
#include <fstream>
#include <sstream>
#include <atomic>
#include <mutex>

// Templateluokka Log_Ptr
template<typename T>
class Log_Ptr {
public:
    // Konstruktori
    Log_Ptr(T* ptr) : object(ptr), ref_count(new std::atomic<int>(1)) {
        log("omistajuus siirretty");
    }

    // Destruktori
    ~Log_Ptr() {
        log("olio tuhottu");
        if (--(*ref_count) == 0) {
            delete object;
            delete ref_count;
        }
    }

    // Sijoitusoperaattori
    Log_Ptr& operator=(const Log_Ptr& other) {
        if (this != &other) {
            // Vähennetään vanhan olion ref countia
            if (--(*ref_count) == 0) {
                delete object;
                delete ref_count;
            }
            // Kopioidaan uusi osoitin ja ref count
            object = other.object;
            ref_count = other.ref_count;
            ++(*ref_count); // Lisätään uuden olion ref countia
        }
        return *this;
    }

    // Lisää luokkaan -> operaattori
    T* operator->() const {
        log("operator->");
        return object;
    }

    // Lisää luokkaan * operaattori
    T& operator*() const {
        log("operator*");
        return *object;
    }

private:
    T* object; // Osoitin viitatun olioon
    std::atomic<int>* ref_count; // Reference count
    std::mutex mtx; // Mutex for thread safety

    // Lokitiedostoon kirjoittaminen
    void log(const std::string& message) const {
        std::lock_guard<std::mutex> lock(mtx); // Lock mutex
        std::ofstream log_file("log_ptr.txt", std::ios::app);
        if (log_file.is_open()) {
            std::time_t current_time = std::time(nullptr);
            log_file << std::asctime(std::localtime(&current_time));
            log_file << message << " " << reinterpret_cast<std::uintptr_t>(object) << std::endl;
        } else {
            std::cerr << "Error: Failed to open log file." << std::endl;
        }
    }
};

// Testiohjelma
int main() {
    // Luodaan uusi olio shared_ptr:n avulla
    std::shared_ptr<int> shared(new int(42));

    // Annetaan shared_ptr Log_Ptr:n huolehdittavaksi
    Log_Ptr<int> logger(shared.get());

    // Käytetään olioita, jotka viittaavat shared_ptr:ään
    {
        Log_Ptr<int> logger_copy = logger; // Kopioidaan logger
        Log_Ptr<int> logger_copy2 = logger_copy; // Kopioidaan toinen logger
    }

    // Tehdään muutama operaatio viitatun olion kanssa
    *logger = 100; // Käytetään * operaattoria
    std::cout << "Value: " << *logger << std::endl; // Käytetään * operaattoria
    logger->operator=(*shared); // Käytetään -> operaattoria

    return 0;
}

