#include <boost/any.hpp>
#include <memory>
#include <tuple>
#include <functional>
#include <iostream>
#include <map>
#include <string>

class Base
{
public:
    virtual void sayHello() = 0;
	virtual ~Base() { }
};
class Fx  : public Base
{
	public:

		Fx(std::string tradeId, std::string create_date)
			: m_tradeId(tradeId)
			, m_createDate(create_date)
		{

		}
		void sayHello()
		{
			std::cout << "Hello from Fx\n";
		}
private:
	std::string m_tradeId;
	std::string m_createDate;
};

class Option  : public Base
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
		std::cout << "Hello from Option\n";
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
		std::cout << "Hello from MM\n";
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

int main()
{

  RegisterFactories("Fx", Action<Base, std::string, std::string>{[] (std::string tradeId, std::string create_date)
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
}


