#include <iostream>
#include <vector>

enum tag2 { three=3, four=4, five=5 };


/// used for specialization (override?)
struct SomeOtherClass
{ 
    friend std::ostream& operator<< (std::ostream& os, SomeOtherClass const & soc)
    {
        os << "SomeOtherClass";
        return os;
    }
};


struct SomeClass 
{
    /// default
    template<typename Tag, typename T>
        void foo(Tag tag, const char * whatever, T const & t)
        {
            std::cout << "default " << __func__ << ": name: " << whatever 
                << ", tag: " << tag  << ", T: " << t << std::endl;
        }
};


/// specialization/override for tag2 + SomeOtherClass
template<>
    void SomeClass::foo(tag2 tag, const char * whatever, SomeOtherClass const & t)
{
    std::cout << "specialized tag2 and SomeOtherClass "  << __func__ << ": name: " << whatever 
              << ", tag: " << tag  << ", T: " << t << std::endl;
}


/// specialization/override for tag2 + vector
template<typename T>
    void SomeClass::foo(tag2 tag, const char * whatever, std::vector<T> const & t)
{
    std::cout << "specialized tag2 and vector<T> "  << __func__ << ": name: " << whatever 
              << ", tag: " << tag  << ", vector! " << std::endl;
}


int main()
{
    enum tag1 { zero, one, two };

    SomeClass sc;
    SomeOtherClass soc;
    std::vector<int> v {1,2,3};

    sc.foo(zero, "first", 255u);
    sc.foo(three, "second", soc); 
    sc.foo(four, "third", v); // fails as it's using the default
}

