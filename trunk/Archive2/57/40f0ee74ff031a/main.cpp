#include <iostream>
#include <cstdarg>


enum class TotoEnum : int{
    Toto1, Toto2
};

std::ostream& operator<<(std::ostream& os, const TotoEnum& value)
{
     switch(value){
        case TotoEnum::Toto1:
        os << "Toto1";
        break;
        case TotoEnum::Toto2:
        os << "Toto2";
        break;
    }
    return os;
}

 
int main()
{
 TotoEnum monEnum{TotoEnum::Toto2};
 std::cout << monEnum;
}