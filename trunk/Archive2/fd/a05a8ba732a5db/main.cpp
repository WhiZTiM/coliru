#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Dummy
{
public:
    Dummy() { cout << "Dummy ctor\n"; }
    Dummy(const Dummy&) { cout << "Dummy cpy ctor\n"; }
    ~Dummy() { cout << "Dummy dtor\n"; }
};

class LongerLived
{
public:
    LongerLived() : fn([]{}) {}
    ~LongerLived() { cout << "LongerLived dtor\n"; fn(); }
    function<void()> fn;
};

int main()
{
    LongerLived l;
    {
        shared_ptr<Dummy> d = make_shared<Dummy>();
        auto fn = [d]()
        {
            cout << "fn called\n";
        };
        l.fn = fn;
    }
}
