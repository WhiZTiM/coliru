#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Dummy // Class que je ne peux pas modifier
{
public:
    Dummy() { cout << "Dummy ctor\n"; }
    Dummy(const Dummy&) { cout << "Dummy cpy ctor\n"; }
    ~Dummy() { cout << "Dummy dtor\n"; }
};

class LongerLived // Class que je ne peux pas modifier
{
public:
    LongerLived() : fn([]{}) {}
    ~LongerLived() { cout << "LongerLived dtor\n"; fn(); }
    function<void()> fn; // Method que je sais appelée dans le dtor de la classe
};

int main()
{
    LongerLived l; // Creation d'une instance de 'LongerLived'
    {
        shared_ptr<Dummy> d = make_shared<Dummy>(); // Creation d'une instance de 'Dummy', et je veux lier sa destruction à celle d'un objet LongerLived
        auto fn = [d]() // Capture de 'Dummy d' (copie provoquant une incrémentation du ref_count du shared_ptr), malgré sa non-utilisation dans la lambda
        {
            cout << "fn called\n";
        };
        l.fn = fn;
    }
}
