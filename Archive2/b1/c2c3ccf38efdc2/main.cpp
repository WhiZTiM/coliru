#include <memory>
#include <tuple>
#include <vector>
#include <cassert>
#include <functional>

template<class FunctionPrototype>
class Event
{
public:

    template<typename... Args>
    void operator()(Args&&... args)
    {
        for (auto const & listener : Listeners)
        {
            if (auto locked = std::get<0>(listener).lock())
                std::get<1>(listener)(std::forward<Args>(args)...);
        }       
    }

    template<typename P, typename Q, typename R, typename... Args>
    void Attach(P(Q::*f)(Args...), std::shared_ptr<R> const & p)
    {
        auto w = std::weak_ptr<R>(p);

        auto l = [w, f](Args... args) {
            if (auto locked = w.lock())
                return (*locked.get().*f)(args...);
            else
                return P();
        };

        Listeners.push_back(std::make_tuple(std::weak_ptr<void>(w), l));        
    }

    typedef std::tuple<std::weak_ptr<void>, std::function<FunctionPrototype>> event_tuple;

    std::vector<event_tuple> Listeners;
};

class Observed : public std::enable_shared_from_this < Observed >
{
public:

    int value;

    void Fire()
    {
        value = 10;

        TheEvent(5, value);

        assert(value != 10);
    }

    Event<void(int, int &)> TheEvent;
};

class Observer : public std::enable_shared_from_this<Observer>
{
public:

    void Attach(std::shared_ptr<Observed> const & observed)
    {
        observed->TheEvent.Attach(&Observer::OnEvent, shared_from_this());
    }

    void OnEvent(int, int & value)
    {
        assert(value == 10);

        value = 1;
    }
};

int main(void)
{
    auto observed = std::make_shared<Observed>();
    auto observer1 = std::make_shared<Observer>();

    observer1->Attach(observed);
    observed->Fire();

    return 0;
}