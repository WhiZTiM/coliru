#include <iostream>
#include <string>
#include <map>
#include <set>

int main()
{
    std::multimap<std::string, std::set<std::string>> authors = {{"Captain", {"Nothing", "Everything"}},
                                                                {"ChajusSaib", {"Foo", "Blah", "Cat"}}};

    for (auto const &auth : authors) {
        std::cout << "Author: " << auth.first << std::endl;
        std::cout << "Books:" << std::endl;
        for (auto const &book: auth.second)
            std::cout << "\t" << book << std::endl;
        std::cout << std::endl;
    }        

    return 0;
}