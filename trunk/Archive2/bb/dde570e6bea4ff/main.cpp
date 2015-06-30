#include <iostream>

using namespace std;

typedef string (*functionPtr)(int previousState, int currentState, int eventId);

string function1(int previousState, int currentState, int eventId);

static functionPtr _ptrAction1 {&function1};

string function1(int p, int c, int e) 
{
    return "test";
}

int main() 
{
    string message = (*_ptrAction1)(5, 4, 3);
    cout << message;
}
