#include <functional>

class what {
public:
    template<class T = void>
    what() {throw;}
};

int main() {
    what wut;
    throw wut;
}