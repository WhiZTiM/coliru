#include <iostream>
#include <type_traits>

namespace
{
    class Number
    {
    public:
        
        explicit Number(int value): m_value{value}
        {}
        
        /// Addition of int
        template<typename T>
        typename std::enable_if<std::is_integral<T>::value, Number>::type operator + (T value) const
        {
            std::cout << "int + " << std::endl;
            return Number{m_value + value};
        }
        
        /// (Implicit) converison to double
        operator double() const
        {
            std::cout << "(double)" << std::endl;
            return static_cast<double>(m_value);
        }
        
        friend std::ostream& operator << (std::ostream&, const Number&);
        
    private:
    
        int m_value;
    };
    
    std::ostream& operator << (std::ostream& os, const Number& x)
    {
        os << "[" << x.m_value << "]";
        return os;
    }
}

int main()
{
    Number x{3};
    
    std::cout << x + 3 << " " << x + 3.4 << std::endl; 
    
    return EXIT_SUCCESS;
}