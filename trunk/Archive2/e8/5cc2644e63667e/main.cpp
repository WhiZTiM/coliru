#include <string>
using namespace std;

class Printer {
public:
    void operator()(const string & a) const {
        printf("string = %s\n", a.c_str());
    }
};

class StringHandler {
public:
    template<class F>
    void handleData(F processor) {
        string hello = "Hello World!!";
        processor(hello);
    }
};

int main() {
    StringHandler h;
    Printer p;
    h.handleData(p);
}