#include <iostream>

int main()
{
    const int i = 20;
    int f = ([](){return i + 3;})();
    int g = ([](int i){return i + 3;})(17);
    std::cout << f << ',' << g << '\n';
}
