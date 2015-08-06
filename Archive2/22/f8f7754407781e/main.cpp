#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

struct Donnees
{
    int A;
    int B;
};

template<typename TStruct>
class Message : public TStruct
{
public:
    Message(void)
    {
    }
    Message(TStruct &aStruct)
    {
        *this=aStruct;
    }
};

int main()
{
    Donnees A;
    A.A = 5;
    Message<Donnees> Test(A);

    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    //std::cout << "Donnees %d" << Test.A << std::endl;
}
