#include <stdio.h>

using namespace std;

struct Lock {
    Lock() { printf("Lock\n"); }
    ~Lock() { printf("Unlock\n"); }
};

struct Value {
    Value() { printf("Create\n"); }
    Value(Value const&) { printf("Copy\n"); }
    ~Value() { printf("Destroy\n"); }
};

Value v = Value();

Value f()
{
    Lock l;
    // modify v
    return v;
}

int main()
{
    Value w = f();
}
