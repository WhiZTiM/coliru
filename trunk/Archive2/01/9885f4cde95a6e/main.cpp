#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
template<typename T>
void Print(T value)
{
 cout << value << endl;
}

template<typename Head, typename... Rail>
void Print(Head head, Rail... rail)
{
 cout << head << ",";
 Print(rail...);
}

int main()
{
 Print(1);                  // 输出：1
 Print(1, "hello");         // 输出：1,Hello
 Print(1, "hello", 'H');    // 输出：1,Hello,H
 return 0;
}