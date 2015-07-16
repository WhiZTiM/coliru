#include <iostream>

class Bar
{
public:
    std::string toString() const // Since you use this on a const reference, method should be const
    {
        return "Bar";
    }
};

std::ostream& operator <<(std::ostream &outStream, const Bar& bar) // If you pass a const reference the toString method must be const as well
{
    outStream << bar.toString();
    return outStream;
}

int main(int argc, char** argv)
{
    Bar b;
    std::cout << b;
    return 0;
}