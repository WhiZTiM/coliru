#include <iostream>
#include <boost/format.hpp>

struct fmt final
{
    fmt(std::string const& spec): imp(spec) {}
    template <class T> fmt& operator<<(T const& data) { imp % data; return *this; }

private:
    boost::format imp;
    friend std::ostream& operator<<(std::ostream& out, fmt const& buf);
};

std::ostream& operator<<(std::ostream& out, fmt const& buf) { return out << buf.imp; }

int main() {
    double d = 0.00000000021;
    std::cout << (fmt("%g.2f\n") << d);
    return 0;
}