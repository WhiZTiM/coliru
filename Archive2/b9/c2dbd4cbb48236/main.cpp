#include <string>
#include <iostream>

using std::string;

struct NoBiggie {
    string rep = "0";

    NoBiggie(string s = "0") : rep(std::move(s)) {}

    operator string() const { return rep; }

    NoBiggie& operator+=(NoBiggie const& rhs) {
        string out;
        auto lb  = rep.rbegin(), le = rep.rend();
        auto rb  = rhs.rep.rbegin(), re = rhs.rep.rend();

        char cc = '0';
        while (lb!=le || rb!=re || cc!='0') {
            char lc = lb!=le? *lb++ : '0';
            char rc = rb!=re? *rb++ : '0';
            
            char r = (lc-'0')+(rc-'0')+cc;
            if (r > '9') {
                out.insert(out.begin(), r-10);
                cc = '1';
            } else {
                out.insert(out.begin(), r);
                cc = '0';
            }
        }

        rep = out;
        return *this;
    }

    friend NoBiggie operator+(NoBiggie a, NoBiggie const& b) { return a+=b; }

    friend std::ostream& operator<<(std::ostream& os, NoBiggie const& n) { return os << n.rep; }
};


int main() {
    for (NoBiggie i("42"); i.rep.size()<100; i+=i)
        std::cout << i << "\n";
}
