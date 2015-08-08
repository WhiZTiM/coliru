#include <iostream>
#include <limits>
#include <sstream>
#include <string>

using namespace std;

int main(){
auto unit = [](auto x) {
    return [=](){ return x; };
};

auto stringify = [&unit](auto x) {
    stringstream ss;
    ss << x;
    return unit(ss.str());
};

auto bind = [](auto u) {
    return [=](auto callback) {
        return callback(u());
    };
};


cout << "Left identity: " << stringify(15)() << "==" << bind(unit(15))(stringify)() << endl;
cout << "Right identity: " << stringify(5)() << "==" << bind(stringify(5))(unit)() << endl;
//cout << "Left identity: " << stringify(15)() << endl;
//cout << "Right identity: " << stringify(5)() << endl;
}