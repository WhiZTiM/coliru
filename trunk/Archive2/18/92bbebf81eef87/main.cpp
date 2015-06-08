#include <vector>
#include <iostream>
#include <typeinfo>
#include <functional>
#include <tuple>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>

template<typename Op,typename ...Ts>
class Observable{
public:
    template<typename T>
    Op& on(std::function<void(T)>&& f)
    {
        get<T>().subscribe(std::forward<std::function<void(T)>>(f));
        return static_cast<Op&>(*this);
    }

    template<typename T>
    Op& notify(const T& value)
    {
        get<T>().notify(value);
        return static_cast<Op&>(*this);
    }
private:
    template<typename T>
    struct ObservableImpl
    {
        void subscribe(std::function<void(T)>&& f)
        {
            observers_.emplace_back(std::move(f));
        }

        void notify(const T& value)
        {
            for(auto& o : observers_)
            {
                o(value);
            }
        }

    private:
        std::vector<std::function<void(T)>> observers_;
    };

    using Observables = std::tuple<ObservableImpl<Ts>...>;
    using Types = boost::mpl::vector<Ts...>;

    template<typename T>
    auto& get()
    {
        using iter = typename boost::mpl::find<Types,T>::type;
        return std::get<iter::pos::value>(observables_);
    }

    Observables observables_;
};


struct Event1{};
struct Event2{};

class AsyncApi
{
public:
    struct async_send : public Observable<async_send,Event1,Event2>
    {
        async_send(AsyncApi* api)
        : api(api) {}

        AsyncApi* api;

        void operator()(int id) {
            api->async_send_impl(*this);
        }
    };

    friend class async_send;

    async_send make_async_send()
    {
        return {this};
    }

private:
    void async_send_impl(async_send& op)
    {
        op.notify(Event1{});
        op.notify(Event2{});
    }
};

int main(int argc,char** argv)
{
    AsyncApi api;

    auto async_send = api.make_async_send()
    .on<Event1>([](auto const& ev)
    {
        std::cout << "Event1" << std::endl;
    })
    .on<Event2>([](auto const& ev)
    {
        std::cout << "Event2" << std::endl;
    })
    ;

    async_send(42);
    return 0;
}
