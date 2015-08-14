#include <iostream>
#include <vector>
#include <memory>

using namespace std;

void __attribute__((format(printf, 1, 2))) f(const char*, ...){}

int main() {
    f("%s");
    return 0;
}
