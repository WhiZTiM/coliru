#include <functional>

template<class Tpe>
class what {
public:
    what(const Tpe & arg) {throw arg;}
};

int main() {
    char meh = 'F';
    what<char> wut = meh;
    throw wut;
}