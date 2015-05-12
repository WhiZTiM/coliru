#include <iostream>
class ArenaInterface
{
    public:
        ArenaInterface(){}
        virtual ~ArenaInterface(){}
        // lots of pure virtuals here
};

class BasicArena : public ArenaInterface
{
public:
    BasicArena() {}
    ~BasicArena() {}
};

int main() {
    BasicArena testarena;
    std::cout << "It works.\n";
    return 0;
}
