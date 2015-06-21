#include <iostream>
#include <memory>

#include <boost/optional.hpp>


template<typename VALTYPE>
class CachedValue
{
private:
    boost::optional<VALTYPE> m_CachedValue;

public:
    CachedValue() : m_CachedValue(boost::none) {};
};


template <typename VALTYPE>
class Base
{
private:
    std::shared_ptr<CachedValue<VALTYPE>> m_CachedValue;

public:
    Base(std::shared_ptr<CachedValue<VALTYPE>> cachedValue) 
        : m_CachedValue(cachedValue) {}
};


class Test : Base<int>
{
public:
    std::shared_ptr<CachedValue<int>> m_CachedValue;
    
    Test() : m_CachedValue(std::make_shared<CachedValue<int>>()), Base(m_CachedValue) {}
};


int main() {
    Test test;
}