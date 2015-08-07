#include <iostream>
#include <string>
using std::string;

int main() {
    string papa = "papa_____________________________________________________________________________________";
    papa.~string();
    string mama = "mama_____________________________________________________________________________________";
    std::cout << "Sou papa ou mama?\n" << papa << "\n\n\n\n" << std::endl;
    return 0;
}