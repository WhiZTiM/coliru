#include <boost/any.hpp>
#include <memory>
#include <tuple>
#include <functional>
#include <iostream>
#include <map>

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

#include <tuple>
#include <iostream>
#include <functional>

namespace helper
{
	template <std::size_t... Ts>
	struct index {};

	template <std::size_t N, std::size_t... Ts>
	struct gen_seq : gen_seq<N - 1, N - 1, Ts...> {};

	template <std::size_t... Ts>
	struct gen_seq<0, Ts...> : index<Ts...>{};
}

template <typename... Ts>
class Action
{
private:
	std::function<Base*(Ts...)> f;
	std::tuple<Ts...> args;
		
public:
 
	Action( std::function<Base*(Ts...)> func, Ts&&... args)
		: f(func)
		, args(std::forward<Ts>(args)...)
	{
	}

	template <typename... Args, std::size_t... Is>
	Base* func(std::tuple<Args...>& tup, helper::index<Is...>)
	{
		return f(std::get<Is>(tup)...);
	}

	template <typename... Args>
	Base* func(std::tuple<Args...>& tup)
	{
		return func(tup, helper::gen_seq<sizeof...(Args)>{});
	}

	Base* act()
	{
		return func(args);
	}
};



class Register
{
	static std::map<std::string, boost::any> factoryMap;

public:
	template<typename ...Args>
	static void  RegisterClass(std::string const& name, Action<Args...> args)
	{
		factoryMap.insert(std::make_pair(name, Action<Args...>(args)));
	}

	template<typename ...Args>
	static Base* Create(std::string const& name)
	{
		Action<Args...> action = boost::any_cast < Action<Args...>>(factoryMap[name]);
		return action.act();
	}
};


std::map<std::string, boost::any> Register::factoryMap;


//REGISTERCLASS("Fx");
//REGISTERCLASS("Option");
//REGISTERCLASS("MoneyMarket");


void SayHello(Base* bp)
{
	bp->sayHello();
}


int main()
{

	Action<std::string, std::string> fxaction{ [](std::string tradeId, std::string create_date)
	{
		return new Fx(tradeId, create_date);
	}, std::string("101"), std::string("20150604") 
	};


	Action<std::string, std::string, std::string> optionAction{ [](std::string tradeId, std::string create_date, std::string strike_date)
	{
		return new Option(tradeId, create_date, strike_date);
	}, std::string("101"), std::string("20150604"), std::string("20150615")
	};


	Action<std::string> mmaction{ [](std::string tradeId)
	{
		return new MoneyMarket(tradeId);
	}, std::string("101")
	};


	Register::RegisterClass("Fx", fxaction);
	Register::RegisterClass("Option", optionAction);
	Register::RegisterClass("MM", mmaction);

	SayHello(Register::Create<std::string, std::string>("Fx"));
	SayHello(Register::Create<std::string, std::string, std::string>("Option"));
	SayHello(Register::Create<std::string>("MM"));
}


