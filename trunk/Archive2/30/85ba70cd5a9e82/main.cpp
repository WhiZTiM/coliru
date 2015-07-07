#include <fstream>
#include <set>

struct Person {
    std::string name;
    std::string nationality;
    std::set<std::string> hobbies;

    friend std::istream& operator>>(std::istream& is, Person& into) {
        size_t n = 0;
        if (getline(is, into.name) &&
            getline(is, into.nationality) &&
            is >> n && is.ignore(1024, '\n')) 
        {
            while (n--) {
                std::string hobby;
                if (getline(is, hobby))
                    into.hobbies.insert(hobby);
                else
                    is.setstate(std::ios::failbit);
            }
        }
        return is;
    }
};


#include <iostream>

int main() {
    std::ifstream ifs("input.txt");

    Person p;
    if (ifs >> p) {
        std::cout << "My information\n";
        std::cout << p.name << "\n";
        std::cout << p.nationality << "\n";
        std::cout << "I have " << p.hobbies.size() << " hobbies:\n";
        size_t counter = 0;
        for(auto const& hobby : p.hobbies) {
            std::cout  << ++counter << ". " << hobby << "\n";
        }
    } else { 
        std::cerr << "Parse failure\n";
    }
}
