#include <iostream>
#include <cstdint>
struct bob
{
    int m_size
}

typedef std::shared_ptr<bob> bob_ptr;
struct controlledBob: public bob
{
    bob_ptr m_bob;
    int m_size;
    
    controlledBob(bob_ptr in): m_bob(in), m_size(in->size){};
}
int main() {

    std::cout << foo();
}
