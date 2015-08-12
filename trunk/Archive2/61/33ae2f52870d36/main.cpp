#include <stdio.h>
#include <iostream>
#include <atomic>
#include <thread>
#include <functional>
#include <chrono>

using namespace std;
using namespace std::chrono;


using oper = bool(*)(bool, bool);

bool and_oper(bool a, bool b);
bool or_oper(bool a, bool b);

bool and_oper(bool a, bool b) {
    return a && b;
}

bool or_oper(bool a, bool b) {
    return a || b;
}


int main() {
    oper op = and_oper;
    bool exp1 = true;
    bool exp2 = true;
    if (op(exp1, exp2)) {
        cout << true << endl;
    }
}