#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>

namespace mylib
{
    struct Angle {
        double degrees = 0, minutes = 0, seconds = 0;

    };

    static std::ostream& operator<<(std::ostream& os, Angle const& angle) {
        std::ostream wrap(os.rdbuf());
        wrap.imbue(std::locale("C"));

        wrap << std::fixed << std::setprecision(std::numeric_limits<double>::digits10) 
            << '(' 
            << angle.degrees << ", " 
            << angle.minutes << ", " 
            << angle.seconds 
            << ')';
        os.setstate(wrap.rdstate());
        return os;
    }

    static std::istream& operator>>(std::istream& is, Angle& angle) {
        std::istream wrap(is.rdbuf());
        wrap.imbue(std::locale("C"));

        auto expect = [&](char const expected) { char actual; return wrap >> actual && actual == expected; };

        expect('(') && (wrap >> angle.degrees) &&
            expect(',') && (wrap >> angle.minutes) &&
            expect(',') && (wrap >> angle.seconds) &&
            expect(')');

        is.setstate(wrap.rdstate());
        return is;
    }
}

int main() {
    std::istringstream iss("(1.24, 9001, 0.000000134)");

    mylib::Angle parsed;
    iss >> parsed;

    std::cout << parsed;
}
