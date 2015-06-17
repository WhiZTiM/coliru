#include <sstream>
#include <iostream>
#include <iomanip>
#include <limits>

namespace mylib
{
    struct Angle {
        double degrees = 0, minutes = 0, seconds = 0;
    };

    std::ostream& operator<<(std::ostream& os, Angle const& angle) {
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

    std::istream& operator>>(std::istream& is, Angle& angle) {
        std::istream wrap(is.rdbuf());
        wrap.imbue(std::locale("C"));

        auto expect = [&](char const expected) { 
            char actual; 

            if (!(wrap >> actual))
                return false;       // state already bad()

            if (actual != expected) // force fail
                wrap.setstate(wrap.rdstate() | std::ios::failbit);

            return actual == expected; 
        };

           expect('(') && (wrap >> angle.degrees)
        && expect(',') && (wrap >> angle.minutes) 
        && expect(',') && (wrap >> angle.seconds) 
        && expect(')');

        is.setstate(wrap.rdstate());
        return is;
    }
}

int main() {
    std::istringstream iss("(1.24, 9001, 0.000000134)");

    mylib::Angle parsed;

    if (iss >> parsed)
        std::cout << "Parsed: " << parsed << "\n";
    else
        std::cout << "Parsing did not succeed\n";
}
