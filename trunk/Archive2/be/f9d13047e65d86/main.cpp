#include <iostream>
#include <bitset>
#include <string>
 
int main()
{
    // функции поиска в строке возвращают npos, если требуемое значение не найдено
    std::string s = "test";
    if(s.find('a') == std::string::npos)
        std::cout << "no 'a' in 'test'\n";
 
    // функции, которые принимают диапазон в качестве аргументов
    // используют npos в качестве индикатора "все до конца строки"
    std::string s2(s, 2, std::string::npos);
    std::cout << s2 << '\n';
 
    std::bitset<5> b("aaabb", std::string::npos, 'a', 'b');
    std::cout << b << '\n';
}