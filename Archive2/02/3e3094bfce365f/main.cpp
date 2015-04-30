#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <tuple>


//http://stackoverflow.com/questions/13065166/c11-tagged-tuple
//http://stackoverflow.com/questions/9400581/template-argument-deduction-with-strongly-typed-enumerations
//http://stackoverflow.com/questions/10742275/stdget-using-enum-class-as-template-argument


template <class Action, typename... T>
class TupleWrapper
{
public:
    std::tuple<T...> _tuple;
    
    template<typename... Args>
    TupleWrapper(Args&&... args) : _tuple(std::forward<Args>(args)...)
    {
    }
    
    template<Action N, typename... Args>
    typename std::tuple_element<static_cast<std::size_t>(N), std::tuple<T...>>::type::result_type call(Args&&... args)
    {
        return std::get<static_cast<std::size_t>(N)>(_tuple)(std::forward<Args>(args)...);
    }
    
    template<Action N>
    typename std::tuple_element<static_cast<std::size_t>(N), std::tuple<T...>>::type get()
    {
        return std::get<static_cast<std::size_t>(N)>(_tuple);
    }
};


enum class Action { Exit = 0, Back, ClickCell };


void onExit() { std::cout << "onExit" << std::endl; }
void onBack() { std::cout << "onBack" << std::endl; }
bool onClickCell(int index) { std::cout << "onClickCell(" << index << ")" << std::endl; return true; }


int main()
{
    auto tuple = TupleWrapper<Action, std::function<void()>, std::function<void()>, std::function<bool(int)>>(&onExit, &onBack, &onClickCell);
    
    tuple.get<Action::Exit>()();
    tuple.get<Action::Back>()();
    tuple.get<Action::ClickCell>()(3);
    
    std::cout << std::endl;
    
    tuple.call<Action::Exit>();
    tuple.call<Action::Back>();
    tuple.call<Action::ClickCell>(3);
}
