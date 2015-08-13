#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// Factory which returns a shared_ptr of type T.
template<class T, class Tag, class... Args>
class NameFactory
{
public:
    typedef std::function<std::shared_ptr<T>(Args...)> Function;

    static NameFactory& instance();

    void registerType(const std::string& type, const Function& createFunction);
    std::shared_ptr<T> createObject(const std::string& type, Args&&... arguments);
private:
    NameFactory() {}

    std::unordered_map<std::string, Function> m_functionMap;
};

template<class T, class Tag, class... Args>
NameFactory<T, Tag, Args...>& NameFactory<T, Tag, Args...>::instance()
{
    static NameFactory<T, Tag, Args...> m_instance;
    return m_instance;
}

template<class T, class Tag, class... Args>
void NameFactory<T, Tag, Args...>::registerType(const std::string& type, const Function& createFunction)
{
    m_functionMap[type] = createFunction;
}

template<class T, class Tag, class... Args>
std::shared_ptr<T> NameFactory<T, Tag, Args...>::createObject(const std::string& type, Args&&... arguments)
{
    auto iter(m_functionMap.find(type));

    if (iter != m_functionMap.end())
    {
        return (iter->second)(std::forward<Args>(arguments)...);
    }

    throw std::logic_error("Cannot find constructor for type '" + type + "'");
}

template<class T, class Tag, class... Args>
class NameFactoryRegistration
{
public:
    typedef NameFactory<T, Tag, Args...> Factory;
    NameFactoryRegistration(const std::string& type, const typename Factory::Function& createFunction)
    {
        Factory::instance().registerType(type, createFunction);
    }
private:
};

class MyBase
{
public:
    typedef std::shared_ptr<MyBase> SPtr;
};

class DerivedA : public MyBase
{
public:
    static SPtr create()
    {
        return SPtr(new DerivedA);
    }

    // Enabling this factory method (and/or the two args method below causes an 'unresolved overloaded function type' error
    //static SPtr create(const std::string& s)
    //{
    //    return SPtr(new DerivedA(s));
    //}

    //static SPtr create(const std::string& s, double d)
    //{
    //    return SPtr(new DerivedA(s,d));
    //}
private:
    DerivedA()
    {
        std::cout << "DerivedA - no args" << std::endl;
    }
    
    DerivedA(const std::string& s)
    {
        std::cout << "DerivedA - one arg: " << s << std::endl;
    }
    
    DerivedA(const std::string& s, double d)
    {
        std::cout << "DerivedA - two args: " << s << " : " << d << std::endl;
    }
};

// Tags to help differentiate the factories
struct NoArgsReg;
struct SingleArgReg;
struct TwoArgReg;

typedef NameFactory<MyBase, NoArgsReg> NoArgsFactory;
typedef NameFactoryRegistration<MyBase, NoArgsReg> NoArgsRegistration;

typedef NameFactory<MyBase, SingleArgReg, const std::string&> SingleArgFactory;
typedef NameFactoryRegistration<MyBase, SingleArgReg, const std::string&> SingleArgRegistration;

typedef NameFactory<MyBase, TwoArgReg, const std::string&, double> TwoArgsFactory;
typedef NameFactoryRegistration<MyBase, TwoArgReg, const std::string&, double> TwoArgsRegistration;

// Register the factory methods into the NameFactory
NoArgsRegistration dAReg0("A", DerivedA::create);
//SingleArgRegistration dAReg1("A", DerivedA::create);
//TwoArgsRegistration dAReg2("A", DerivedA::create);


int main()
{
    auto object0(NoArgsFactory::instance().createObject("A"));
    
    // Not registered, 
    //auto object1(SingleArgFactory::instance().createObject("A","testString"));
    //auto object2(TwoArgsFactory::instance().createObject("A","testString",3.142));
    
    return 0;
}
