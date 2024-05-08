#include <iostream>
#include <vector>
#include <algorithm>

// Vähentää HP:tä 100:lla tai asettaa sen nollaan, jos se on jo 100 tai vähemmän
void reduceHP(int& hp) {
    hp = (hp > 100) ? hp - 100 : 0;
}

int main() {
    // Luodaan vektori vihollisten HP:stä
    std::vector<int> enemyHP = {150, 70, 200, 100, 50};

    // Käytetään std::for_each-algoritmia erillisenä funktiona
    std::for_each(enemyHP.begin(), enemyHP.end(), reduceHP);

    // Käytetään std::sort-funktiota laskevaan järjestykseen lambda-funktiolla
    std::sort(enemyHP.begin(), enemyHP.end(), [](int a, int b) { return a > b; });

    // Tulostetaan vektori
    std::cout << "Vihollisten HP laskevassa järjestyksessä: ";
    for (int hp : enemyHP) {
        std::cout << hp << " ";
    }
    std::cout << std::endl;

    return 0;
}
