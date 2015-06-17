#include <iostream>
#include <cstring>
void add(char * _str, int _i)
{
    if (_str[_i] > 'z')
        _str[_i] = 'A';
    else if (_str[_i] > 'Z' && _str[_i] < 'a')
    {
        _str[_i] = 'a';
        if (_i > 0)
            _str[_i - 1] = _str[_i - 1] == ' ' ? 'a' : _str[_i - 1] + 1;
    }
}
void next(char * _str)
{
start:
    _str[2]++;
    add(_str, 2);
    add(_str, 1);
    add(_str, 0);
    std::cout << _str << std::endl;
    if (strcmp(_str, "ZZZ"))
        goto start;
}

int main(int argc, char *argv[])
{
    char str[4] = "  `";
    next(str);
}