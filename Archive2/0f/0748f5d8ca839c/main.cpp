#include <iostream>

class abc
{
public:
    template<typename typ>
    void integerA(typ x);
};

template<typename typ>
void abc::integerA(typ x) {
  std::cout << "other" << std::endl;
}

template<>
void abc::integerA(int x) {
  std::cout << "int" << std::endl;
}

int main() {
  abc A;
  A.integerA(1);
  A.integerA(1.0);
}