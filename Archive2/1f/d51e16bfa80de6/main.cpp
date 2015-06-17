#include <stdexcept>
#include <iostream>

struct Angle {
    double degrees = 0, minutes = 0, seconds = 0;
};

namespace { 
    bool expect(std::istream& is, char expected) {
        char actual; 

        if (!(is >> actual && actual == expected))
            throw std::runtime_error(std::string("Expected '") + expected + "'");

        return true;
    }

    Angle readAngle(std::istream& is) {
        Angle angle;

        if (   expect(is, '(') && (is >> angle.degrees)
            && expect(is, ',') && (is >> angle.minutes) 
            && expect(is, ',') && (is >> angle.seconds) 
            && expect(is, ')'))
        {
            return angle;
        } else {
            throw std::runtime_error("Input error");
        }
    }
}

int main() {
    Angle parsed = readAngle(std::cin);
    std::cout << "Parsed: " << parsed.degrees << ", " << parsed.minutes << ", " << parsed.seconds << "\n";
}
