# include <iostream>
# include <sstream>
int main()
{
std::istringstream in {"C++ Patea Traseros!!!!"};
in.get(*std::cout.rdbuf());
}