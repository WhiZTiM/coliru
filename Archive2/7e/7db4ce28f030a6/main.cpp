#include <iostream>
#include <string>
#include <vector>

class Noisy {
public:
    ~Noisy() { std::cout << "D-tor\n"; }
};

class My {
public:
  Noisy const& n;
  My(Noisy const& n) : n(n) { }
};

int main()
{
    My* m;
    {
        m = new My(Noisy());
    }
    std::cout << "Out of scope\n";
    delete m;
}
