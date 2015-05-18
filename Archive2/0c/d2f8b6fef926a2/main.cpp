#include <string>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <array>
 
int main()
{
    // конструктор использует aggregate initialization
    std::array<int, 3> a1{ {1,2,3} };  // требуются двойные фигурные скобки,
    std::array<int, 3> a2 = {1, 2, 3}; // за исключением операций присваивания
    std::array<std::string, 2> a3 = { {std::string("a"), "b"} };
 
    // поддерживаются обобщённые алгоритмы
    std::sort(a1.begin(), a1.end());
    std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(std::cout, " "));
 
    // поддерживается randed for цикл
    for(auto& s: a3)
        std::cout << s << ' ';
}