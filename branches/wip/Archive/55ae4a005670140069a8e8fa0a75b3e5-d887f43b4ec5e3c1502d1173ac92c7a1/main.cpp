#===============================================================================
# number.cpp
#===============================================================================
cat << COLIRU_EOF > number.cpp
int number = 42;
COLIRU_EOF


#===============================================================================
# main.cpp
#===============================================================================
cat << COLIRU_EOF > main.cpp
#include <iostream>

extern int number;

int main()
{
    std::cout << "number: " << number << std::endl;
}
COLIRU_EOF


#===============================================================================
# build commands
#===============================================================================
g++ -c number.cpp
g++ -c main.cpp
g++ *.o
./a.out
