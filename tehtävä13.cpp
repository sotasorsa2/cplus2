#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::move

int main() {
    // Vaihe a)
    std::string s1 = "kissa";
    std::string s2;

    std::cout << "Vaihe a) Ennen sijoitusta: s1 = " << s1 << ", s2 = " << s2 << std::endl;

    // Sijoitetaan s2 s1:een
    s1 = s2;

    std::cout << "Vaihe a) Jälkeen sijoituksen: s1 = " << s1 << ", s2 = " << s2 << std::endl;

    // Vaihe b)
    std::string s3 = "koira";

    std::cout << "Vaihe b) Ennen sijoitusta: s1 = " << s1 << ", s2 = " << s2 << ", s3 = " << s3 << std::endl;

    // Sijoitetaan s3 s1:een käyttäen std::movea
    s1 = std::move(s3);

    std::cout << "Vaihe b) Jälkeen sijoituksen: s1 = " << s1 << ", s2 = " << s2 << ", s3 = " << s3 << std::endl;

    // Vaihe c)
    std::vector<std::string> string_vector;

    std::cout << "Vaihe c) Ennen sijoitusta: vektorin koko = " << string_vector.size() << std::endl;

    // Lisätään s3 vektoriin käyttäen push_backia
    string_vector.push_back(s3);

    std::cout << "Vaihe c) Jälkeen sijoituksen push_backilla: vektorin koko = " << string_vector.size() << std::endl;

    // Palautetaan s3 alkuperäiseen tilaansa ja sijoitetaan se uudelleen käyttäen std::movea
    s3 = "koira";
    string_vector.push_back(std::move(s3));

    std::cout << "Vaihe c) Jälkeen sijoituksen std::move: vektorin koko = " << string_vector.size() << std::endl;

    return 0;
}
