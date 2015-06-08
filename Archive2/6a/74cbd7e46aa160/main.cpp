#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <functional>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>

template<typename T>
struct FunctionWrapper
{
    FunctionWrapper(std::size_t id,std::function<void(T)>&& f)
    : id_(id),f_{std::move(f)} {}
    
    FunctionWrapper(FunctionWrapper<T>&& other)
    : id_(other.id_),f_{std::move(other.f_)}
    {
        other.id_ = std::numeric_limits<std::size_t>::max();
    }
    
    FunctionWrapper& operator= (FunctionWrapper<T>&& other) 
    {
        id_ = other.id_;
        other.id_ = std::numeric_limits<std::size_t>::max();
        f_ = std::move(other.f_);
        return *this;
    }
    
    std::size_t id_;
    std::function<void(T)> f_;
};


template<typename T,typename ...Ts>
class Observable
{
public:
    template<typename U>
    T& on(std::function<void(U)>&& f)
    {
        get<U>().subscribe(0,std::move(f));
        return static_cast<T&>(*this);   
    }
    
    template<typename U,typename OutIter>
    T& on(OutIter it,std::function<void(U)>&& f)
    {
        it = 1;
        get<U>().subscribe(1,std::move(f));
        return static_cast<T&>(*this);
    }

    template<typename U>
    T& notify(U const& ev)
    {
        get<U>().notify(ev);
        return static_cast<T&>(*this);
    }
    
private:
    template<typename U>
    struct ObservableImpl
    {
        void notify(U const& ev)
        {
            for(auto& o : observers_)
            {
                o.f_(ev);
            }
        }
        
        void subscribe(std::size_t id,std::function<void(U)>&& f)
        {
            observers_.emplace_back(id,std::move(f));
        }
        
        void unsubscribe(std::size_t id)
        {
            observers_.erase(
                std::begin(observers_),std::end(observers_),
                [id](auto const& o){return id == o.id_;});
        }
        
        std::vector<FunctionWrapper<U>> observers_;
    };

    using ObservableTypes = boost::mpl::vector<Ts...>;
    using ObservableTuple = std::tuple<ObservableImpl<Ts>...>;
    
    template<typename U> 
    ObservableImpl<U>& get() noexcept
    {
        using it = typename boost::mpl::find<ObservableTypes,U>::type;
        return std::get<it::pos::value>(observables_);
    }

    ObservableTuple observables_;
};

struct Event1{};
struct Event2{};
struct Event3{};

struct O : public Observable<O,Event1,Event2,Event3>
{};

int main()
{
    O o;
    o
    .on<Event1>([](auto const&)
    {
        std::cout << "Event1" << std::endl;
    })
    .on<Event2>([](auto const&)
    {
        std::cout << "Event2" << std::endl;
    });
    
    o.notify(Event1{});
    o.notify(Event2{});
    
    std::vector<std::size_t> ids;
    auto id = std::back_inserter(ids);
    
    o.on<Event3>(id,[](auto const&)
    {
        std::cout << "Event3" << std::endl;
    });
    
    o.notify(Event3{});
    return 0;
}
