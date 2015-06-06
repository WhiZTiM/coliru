#include <iostream>

namespace math{ 
template <int I, int J>
struct Plus{
    constexpr static int Value_ = I + J;
};

template <int I, int J = 5>
struct Minus; // template declaration.
}

// global-scope template declaration?
//template <int I, int J>
//struct math::Minus; // error: does not name a type (if no declaration @ line 9)
                      // error: invalid use of math::Minus w/o argument list
                      //                             (if declaration @ line 9)


namespace math{

    template <int I, int J>
    struct Minus{
        static int value();
    };
    
    namespace{ // anonymous namespace
    
        //template <int I, int J = 5>
        //struct Minus; compiles, but is a declaration of another class,
                       // which I assume hides the math scope class
        
        // error: incomplete type--I assume this means the above 
        // doesn't declare math::Minus, but math::<anon>::Minus
        //constexpr int twominus5= Minus<2>::value(); 
    
    } // end anonymous namespace
    
} // end math namespace

//template <int I, int J>
//class math::Minus; // error: invalid use of math::Minus w/o argument list

template <int I, int J>
int math::Minus<I,J>::value(){return I - J;}


int main()
{
    std::cout 
        << math::Minus<5,1>::value() << std::endl
        << math::Minus<0>::value() << std::endl;
}
