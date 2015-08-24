#include <iostream>

#define DOIT_0(X)
#define DOIT_1(X) X
#define CONCAT_(X, Y) X ## Y
#define MAYBE(X) CONCAT_(DOIT_, X)

#define BAR(X) MAYBE(X)(  std::cout << "hi";  )

#define YES 1
#define NO 0

int main()
{
    std::cout << "NOTHING: ";
    BAR(NO);
    std::cout << '\n';
    std::cout << "SOMETHING: ";
    BAR(YES);
    std::cout << '\n';
}
