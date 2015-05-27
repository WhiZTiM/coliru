#include <iostream>
#include <array>

int main() {
    std::array<std::string, 14> x = {
        "ik", "heb", "daarvoor", "een", "extra", "kans", "gehad", "van", "de", "examen", "commisie", "omdat", "het", "voornamelijk"    
    };
    
    for (auto&& woord : x)
        std::cout << woord << " ";
    std::cout << x[14] << std::endl;
}