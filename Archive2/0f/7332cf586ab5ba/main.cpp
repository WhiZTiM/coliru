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

class A
{
public:
    A(void **fmq_ptr) : m_fmq(fmq_ptr)
    {
    };
    
    void** m_fmq;
    
    void *getFmq()  {return *m_fmq;};
    
};


void* a = NULL;

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    std::cout << words << std::endl;
    

    
    A CA(&a);
    
    std::cout << "new: " << CA.getFmq() << std::endl;
    
    a = (void*) 0x666;
    
    std::cout << "new2 " << CA.getFmq() << std::endl;
}
