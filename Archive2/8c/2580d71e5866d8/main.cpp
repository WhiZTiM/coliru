#include <iostream>
#include <sstream>
#include <ctime>

std::istream &operator>>(std::istream &is, struct tm &t) { 
    char ign;
    is >> t.tm_year >> ign >> t.tm_mon >> ign >> t.tm_mday;
    t.tm_year -= 1900;
    --t.tm_mon;
    mktime(&t);
    return is;
}

std::ostream &operator<<(std::ostream &os, tm const &t) { 
    char buffer[1024];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &t);
    return os << buffer;
}

int main() {
    std::istringstream in("2015-07-26");
    tm im_lazy{};
    in >> im_lazy;
    std::cout << im_lazy;
}