#include <boost/range/any_range.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <vector>
#include <memory>
#include <cstdio>

class DummyElement
{
public:
    float f_;
};

using ElementRange = boost::any_range < DummyElement*, boost::bidirectional_traversal_tag >;

using DummyElementUPtr = std::unique_ptr < DummyElement > ;
using Int = int;

class BoostAnyTest
{
public:
    BoostAnyTest()
    { 
        for (int i = 0; i < 10; ++i)
        {
            auto element = DummyElementUPtr(new DummyElement());
            printf("BoostAnyTest::ctor() 0x%p\n", element.get());

            c_.emplace_back(std::tuple<Int, DummyElementUPtr>(i, std::move(element)));
        }
    }

public:
    ElementRange GetAll();

private:
    using _ContainerType = std::vector < std::tuple<Int, std::unique_ptr<DummyElement>> > ;
    _ContainerType    c_;
};


ElementRange
BoostAnyTest::GetAll()
{
    auto transform = [ ] (const _ContainerType::value_type& v) -> DummyElement*
    {
        return std::get<1>(v).get();
    };

    return c_ | boost::adaptors::transformed(transform);
}


int main()
{
    BoostAnyTest    any;

    auto range = any.GetAll();

    std::for_each(std::begin(range), std::end(range), [ ] (DummyElement* element)
    { 
        printf("TestBoostAnyRange() 0x%p\n", element);
    });
}