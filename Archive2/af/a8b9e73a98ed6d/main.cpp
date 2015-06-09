#include <memory>
#include <cassert>

template<typename X>
struct pathological {
    std::shared_ptr<X> value;
    
    pathological() = default;
    pathological(pathological&&) = default;
    
    pathological(std::shared_ptr<X> value): value(std::move(value)) {}
    
    // a copy constructor by everything but name
    pathological<X> share() const { return { value }; }
};

int main()
{
    pathological<int> p(std::make_shared<int>(42));
    auto q = p.share();
    assert( p.value.get() == q.value.get() );
    
    // fine
    auto x = std::move(p);
    assert( x.value.get() == q.value.get() );
    
    // not allowed
    // auto y = x;
}
