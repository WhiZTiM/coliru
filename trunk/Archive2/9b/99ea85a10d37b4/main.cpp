#include <iostream>

unsigned long long hash(std::string const &val) {
    unsigned long long hash = 0;
    
    for(size_t i = 0; i < val.size(); ++i)
    {
        hash += ((i + 1) * (val[i] -3)) % 51;
    }
    
    return hash;
}

void show_hash(std::string const &passwd)
{
    std::cout << passwd << " " << hash(passwd) << std::endl;
}

int main() {
    show_hash("hunter2");
    show_hash("password");
}
