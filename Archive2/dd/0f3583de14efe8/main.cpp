#include <iostream>

class SomeClass
{
public:
    SomeClass() { }
    ~SomeClass() { }
    void tprintf(const char* format);

    template<typename T, typename... Targs>
    void tprintf(const char* format, T value, Targs... Fargs);
};

void SomeClass::tprintf(const char* format) // base function
{
    std::cout << format;
}

template<typename T, typename... Targs>
void SomeClass::tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            tprintf(format + 1, Fargs...); // recursive call
            return;
        }
        std::cout << *format;
    }
}

int main()
{
    SomeClass someClass();

    someClass.tprintf("% world% %\n", "Hello", '!', 123);
}