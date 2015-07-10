#include <iostream>
#include <array>
#include <utility>
#include <string>

struct arr{
int a,b,c;
};

struct arr2{
int a,b;
std::string c;
};

struct arr3{ 
    //float a,b,c;
};

using arr4 = arr;

template<typename TData>
class Phenotype{
public:
    template<typename ...T>
    void lala(T&&...t){
        m_array = { t... };
    }
    
    TData m_array;
};

using T1 = Phenotype<arr>;
using T2 = Phenotype<arr2>;
using T3 = Phenotype<arr3>;
using T4 = Phenotype<arr4>;

class Comp1 : public T1,public T2,public T3{ };
class Comp2 : public T1{ };
class Comp3 : public T4{ };

int main()
{
    // used like
    Comp1 comp1;
    Comp2 comp2;
    Comp3 comp3;
    
    
    comp1.T2::lala(1, 2, "lala");
    comp1.T1::lala(1, 2, 3);
    comp2.T1::lala(5, 6, 7);
    comp1.Phenotype<arr>::lala(10, 20, 30);
    comp1.T3::lala( );
    comp3.T4::lala(53, 63, 73);
     
    std::cout << comp1.T1::m_array.a << ", "<<  comp1.T1::m_array.b <<  ", " << comp1.T1::m_array.c << std::endl;
    std::cout << comp1.T2::m_array.a << ", "<<  comp1.T2::m_array.b <<  ", " << comp1.T2::m_array.c << std::endl;
    std::cout << comp2.T1::m_array.a << ", "<<  comp2.T1::m_array.b <<  ", " << comp2.T1::m_array.c << std::endl;
    
    std::cout << comp3.T4::m_array.a << ", "<<  comp3.T4::m_array.b <<  ", " << comp3.T4::m_array.c << std::endl;
    
   
}