#include <iostream>
#include <string>
using std::string;

int main() {
    string papa = "papa____________________________________________________________________________________";
    papa.~string();
    string mama = "mama";
    std::cout << "Sou papa ou mama?\n" << papa << "\n\n\n\n" << std::endl;
    return 0;
}