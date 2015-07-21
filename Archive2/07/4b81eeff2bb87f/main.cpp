#include <type_traits> 
#include <iostream>

class X
{
    public:
        template <typename CHECK, std::enable_if_t< std::is_floating_point<CHECK>::value>* =nullptr >
            void Do()
            {
                std::cout << "yes" << std::endl;
            }

        template <typename CHECK, std::enable_if_t< !std::is_floating_point<CHECK>::value>* =nullptr>
            void Do()
            {
                std::cout<< "no" << std::endl;
            }

};

int main()
{
    X x;
    x.Do<float>();
}