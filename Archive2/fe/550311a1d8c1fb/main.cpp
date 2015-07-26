#include <iostream>
#include <string>
#include <vector>

void foo(std::vector<std::string> args) {return;}

int main() {
    foo({"asd","dsa"});          // error.
}