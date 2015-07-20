#include <iostream>

struct DangerousA {
    DangerousA() : a(5) { }

    virtual ~DangerousA() { }

    virtual void abc() {
        std::cout << "ABCDEFG..." << std::endl;
    }

    virtual void printA() {
        std::cout << "A: " << a << std::endl;
    }

    int a;
};

struct DangerousB {
    DangerousB() : a(6) { }

    virtual ~DangerousB() { }

    virtual void printA() {
        std::cout << "B: " << a << std::endl;
    }

    int a;
};

int main()
{
    std::cout << "Starting with a class DangerousA & DangerousB, both are unrelated" << std::endl;
    std::cout << "Let's see if we can get them to jump vtables..." << std::endl;

    DangerousA* a = new DangerousA();
    DangerousB* b = new DangerousB();

    a->printA();
    (reinterpret_cast<DangerousB*>(a))->printA();

    std::cout << "Done" << std::endl;

    delete a;
    delete b;
}