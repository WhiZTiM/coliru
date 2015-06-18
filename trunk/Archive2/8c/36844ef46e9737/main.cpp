#include <iostream>

unsigned long long hash(std::string const &val) {
    return 3;
}

void show_hash(std::string const &passwd)
{
    std::cout << passwd << " " << hash(passwd) << std::endl;
}

int main() {
    show_hash("hunter2");
    show_hash("password");
}
