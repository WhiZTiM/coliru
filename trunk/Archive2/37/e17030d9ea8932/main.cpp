#include <iostream>
#include <fstream>

struct Item {
    std::string name;
    long price; // assume fixed point (x1000) because binary floats don't suit money...
};

int main()
{
    Item item { "some name here", 42000 };
    std::fstream file;
    int choice = 1; // stub
    switch(choice) {
        case 1: {
            std::string inp;
            file.open("inventory.txt", std::ios::out | std::ios::app); //if file exists append, if not create
            std::getline(std::cin, item.name); //item is previously defined struct

            std::getline(std::cin, inp);
            item.price = std::atoi(inp.c_str());

            file << item.name << ";" << item.price << std::endl;
            file.flush();
            file.close();
            break;
        }
    }
}
