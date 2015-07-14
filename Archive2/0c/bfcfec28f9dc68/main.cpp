#include <functional>
#include <iostream>

struct mav {};
struct msg {};

#ifdef DEBUG
#error DEBUG is defined
#endif

#ifdef _DEBUG
#error _DEBUG is defined
#endif

#ifdef ENABLE_ASSERTS
#error ENABLE_ASSERTS is defined
#endif

void decode(const mav *m, msg *g) { std::cout << "mav: " << m << ", msg: " << g << std::endl; }

int main()
{   
    mav *m = (mav*)2;
    msg *g = (msg*)3;
    
    std::function<void(const mav *)> func = std::bind(decode,std::placeholders::_1,g);
    
    func(m);
    
    return 0;
}