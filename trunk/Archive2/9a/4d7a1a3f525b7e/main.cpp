#include <iostream>

bool expect(std::istream& is, char match) {
    char input;
    
    if (!(is >> input && input == match))
        return false;
    else
        return true;
}

int main() {
    double degrees = 0;
    double minutes = 0;
    double seconds = 0;
    
    if (expect(std::cin, '(') && (std::cin >> degrees)
        && expect(std::cin, ',') && (std::cin >> minutes) 
        && expect(std::cin, ',') && (std::cin >> seconds) 
        && expect(std::cin, ')')) {
        std::cout << "Angle: " << degrees << "d " << minutes << "\' " << seconds << "\" " << "\n";        
    } else {
        std::cout << "ERROR!\n";   
        return 1;
    }
    return 0;

}
