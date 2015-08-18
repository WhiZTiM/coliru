#include <string>
#include <array>
#include <iostream>

struct person {
    std::string name;
    std::string surname;
    int age;
    float wage;
}; 


int main() {
    std::array<person, 2> people{{
        {"John", "Smith", 23, 100.0},
        {"Mary", "Smith", 21, 120.0}
    }};

    for (auto& p : people) {
        int k = 5;
        while (k > 0) {
            p.age += 1;
            p.wage *= 1.1;
            k--;
        }
    }

    std::cout<<"-----------------------------\n";
    for (auto const& p : people) {
        std::cout << "New Age:" << p.age << '\n'; 
        std::cout << "New Wage:" << p.wage << '\n';
    }
    std::cout<<"-----------------------------\n";
}