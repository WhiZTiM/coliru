#include <boost/any.hpp>
#include <memory>
#include <tuple>
#include <functional>
#include <iostream>
#include <map>
#include <string>

/*
class Base
{
    public:
    virtual void sayHello() = 0;
    virtual ~Base() {}
};
class Fx : public Base
{
    public:

    Fx(std::string tradeId, std::string create_date)
        : m_tradeId(tradeId)
        , m_createDate(create_date)
    {

    }
    void sayHello()
    {
        std::cout << "TradeId:" << m_tradeId << "\t"
            << "CreateDt:" << m_createDate << "\n";
    }
    private:
    std::string m_tradeId;
    std::string m_createDate;
};

class Option : public Base
{
    public:
    Option(std::string tradeId, std::string create_date, std::string strike_date)
        : m_tradeId(tradeId)
        , m_createDate(create_date)
        , m_strikeDate(strike_date)
    {

    }


    void sayHello()
    {
        std::cout << "TradeId:" << m_tradeId << "\t"
            << "CreateDt:" << m_createDate << "\t"
            << "StrikeDate:" << m_strikeDate << "\n";

    }

    private:
    std::string m_tradeId;
    std::string m_createDate;
    std::string m_strikeDate;

};

class MoneyMarket : public Base
{
    public:
    MoneyMarket(std::string tradeId)
        : m_tradeId(tradeId)
    {

    }

    void sayHello()
    {
        std::cout << "TradeId:" << m_tradeId << "\n";
    }

    private:
    std::string m_tradeId;
};



namespace helper
{
	template <std::size_t... Ts>
	struct index {};

	template <std::size_t N, std::size_t... Ts>
	struct gen_seq : gen_seq<N - 1, N - 1, Ts...> {};

	template <std::size_t... Ts>
	struct gen_seq<0, Ts...> : index<Ts...>{};
}

template <typename T, typename... Ts>
class Action
{
    private:
    std::function<T*(Ts...)> f;

    public:

    Action(std::function<T*(Ts...)> func)
        : f(func)
    {
    }

    template <typename... Args, std::size_t... Is>
    T* func(std::tuple<Args...>& tup, helper::index<Is...>)
    {
        return f(std::get<Is>(tup)...);
    }

    template <typename... Args>
    T* func(std::tuple<Args...>& tup)
    {
        return func(tup, helper::gen_seq<sizeof...(Args)>{});
    }

    template<typename... Args> 
    T* act(std::tuple<Args...>&& tup)
    {
        return func(tup);
    }
};



class Register
{
    static std::map<std::string, boost::any> factoryMap;

    public:
    template<typename T, typename ...Args>
    static void  RegisterClass(std::string const& name, Action<T, Args...> args)
    {
        factoryMap.insert(std::make_pair(name, Action<T, Args...>(args)));
    }

    template<typename T, typename ...Args>
    static T* Create(std::string const& name, Args&&... args)
    {
        Action<T, Args...> action = boost::any_cast < Action<T, Args...>>(factoryMap[name]);
        return action.act(std::tuple<Args...>(std::forward<Args>(args)...));
    }
};


std::map<std::string, boost::any> Register::factoryMap;

template<typename T, typename... Args>
void RegisterFactories(std::string name, Action<T, Args...> a)
{
    Register::RegisterClass(name, a);
}

void SayHello(Base* bp)
{
    bp->sayHello();
}



template<typename ...Args>
struct TypeOfArgs
{
    typedef typename std::common_type<Args...>::type type;
};

template<typename Func, typename First, typename Second>
bool AllOfHelper(Func f, First a, Second b)
{
    return f(a, b);
}

template<typename Func,  typename First, typename Second, typename...Rest>
bool AllOfHelper(Func f, First a, Second b, Rest... rest)
{
    return f(a, b) && AllOfHelper(f, b, rest...);
}



template<typename Func=std::equal_to<typename TypeOfArgs<Rest...>::type>,  class... Rest>
bool AllOf(Func f, Rest... rest)
{
    return  AllOfHelper(f, rest...); 
}


*/

bool AllStringsEqual(const char* l, const char* r)
{
    return ::strcmp(l, r) == 0;
}


template<typename T, typename Comparator = std::equal_to<T>>
struct AllOf
{
    Comparator m_c;

    AllOf() : m_c{} { }
    AllOf(Comparator c)
        : m_c(c)
    { }

    public:
    template<typename Head, typename...Tail>
    bool operator()(Head h, Tail... t)
    {
        return AllOfHelper(h, t...);
    }


    private:

    template<typename First, typename Second>
    bool AllOfHelper(First a, Second b)
    {
        return m_c(a, b);
    }

    template<typename First, typename Second, typename... Rest>
    bool AllOfHelper(First a, Second b, Rest... r)
    {
        return m_c(a, b) && AllOfHelper(b, r...);
    }

};



int main()
{

/*  RegisterFactories("Fx", Action<Base, std::string, std::string>{[] (std::string tradeId, std::string create_date)
    {
        return new Fx(tradeId, create_date);
    }});

    RegisterFactories("Option", Action<Base, std::string, std::string, std::string>{[] (std::string tradeId, std::string create_date, std::string strike_date)
    {
        return new Option(tradeId, create_date, strike_date);
    }});

    RegisterFactories("MM", Action<Base, std::string>{[] (std::string tradeId)
    {
        return new MoneyMarket(tradeId);
    }});


     //Once you have the data, pass it to create the factories.

    SayHello(Register::Create<Base, std::string, std::string>("Fx", std::string("101"), std::string("20150604")));
    SayHello(Register::Create<Base, std::string, std::string, std::string>("Option", std::string("101"), std::string("20150604"), std::string("20150615")));
    SayHello(Register::Create<Base, std::string>("MM", std::string("101")));
    

    
    std::cout << AllOf(1, 1,1,1) << "\n";
    std::cout << AllOf(1, 1,2) << "\n";
    std::cout << AllOf(1,2) << "\n";
    std::cout << AllOf(1,1) << "\n";
    std::cout << AllOf(1,1,2,2) << "\n";
    
    std::cout << AllOf([] (const char* l, const char* r) { return strcmp(l, r) == 0; }, "jagan", "jagan", "roopesh") << "\n";
    
*/
    std::cout << AllOf<int>{} (1, 1) << "\n";
    std::cout << AllOf<int>{} (1, 1, 1) << "\n";
    std::cout << AllOf<int>{} (1, 1,2, 1) << "\n";
    std::cout << AllOf<int>{} (1, 1,2,2) << "\n";


    typedef bool(*Comp)(const char*, const char*);


    std::cout << AllOf<const char*, Comp>{ AllStringsEqual }("jagan", "jagan", "roopesh") << "\n";
    std::cout << AllOf<const char*, Comp>{ AllStringsEqual }("jagan", "jagan", "jagan") << "\n";
    

}


