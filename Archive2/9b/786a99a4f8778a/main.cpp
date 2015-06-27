#include <iostream>
#include <string>
#include <map>
#include <set>

int main()
{
    std::multimap<std::string, std::set<std::string>> authors = {{"Captain", {"Nothing", "Everything"}}, {"ChajusSaib", {"Foo", "Blah", "Cat"}}};

    for (auto& author : authors) {
        std::cout << "Author:\t" << author.first << "\nBook:\t\t"; 
        for (auto& book : author.second) {
            std::cout << book << " ";
        }
        std::cout << '\n';
    }
}