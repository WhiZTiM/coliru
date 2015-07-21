#include <iostream>

#include <cstdio>

using namespace std;
int main()

{

char str[80];

cout << "Введите строку: ";

gets(str); // Считываем строку с клавиатуры.

cout << "Вот ваша строка: ";

cout << str;

return 0;

}
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
