#include <utility>

class Object
{
    public:
    Object(int, char, bool) {}
};

template <typename T>
class Builder
{
    public:
    template <typename... Args>
    Builder(Args&&... args) : obj(std::forward<Args>(args)...) {}
    
    private:
    T obj;
};

int main()
{
    Builder<Object> b(0, '0', false);
}
