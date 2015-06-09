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
    struct Scope;

    Scope makeScope()
    {
        return {this};
    }

    template<typename U>
    T& on(std::function<void(U)>&& f)
    {
        get<U>().subscribe(0,std::move(f));
        return static_cast<T&>(*this);   
    }
    
    template<typename U>
    T& on(Scope& scope,std::function<void(U)>&& f)
    {
        const size_t id{1};
        scope.add(id);
        get<U>().subscribe(id,std::move(f));
        return static_cast<T&>(*this);
    }

    template<typename U>
    T& notify(U const& ev)
    {
        get<U>().notify(ev);
        return static_cast<T&>(*this);
    }
    
    T& unsubscribe(std::size_t id)
    {
        
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

////////////////////////////////////////// impl //////////////////////////////////
template<typename T,typename ...Ts>
struct Observable<T,Ts...>::Scope
{
    Scope(Observable<T,Ts...>* observable)
    : observable_{observable} {}
        
    ~Scope()
    {
        if(observable_)
        {
//            for(auto id : ids_)
//            {
//                observable_.unsubscribe(id);
//            }
        }
    }
        
    Scope(Scope&& other)
    : observable_{other.observable_},
      ids_{std::move(other.ids_)}
    {
        other.observable_ = nullptr;    
    }
        
    Scope& operator = (Scope&& other)
    {
        ids_ = std::move(other.ids_);
        observable_ = other.observable_;
        other.observable = nullptr;
    }
        
    void add(std::size_t id) 
    {
        ids_.push_back(id);
    }
private:
    Observable<T,Ts...> * observable_;
    std::vector<std::size_t> ids_;
};


struct Event1{};
struct Event2{};
struct Event3{};

struct O : public Observable<O,Event1,Event2,Event3>
{};

int main()
{
    O o;
    o.on<Event1>([](auto const&)
    {
        std::cout << "Event1" << std::endl;
    })
    .on<Event2>([](auto const&)
    {
        std::cout << "Event2" << std::endl;
    });
    
    o.notify(Event1{});
    o.notify(Event2{});
    
    auto scoped = o.makeScope();
    o.on<Event3>(scoped,[](auto const&)
    {
        std::cout << "Event3" << std::endl;
    });
    
    o.notify(Event3{});
    
    auto scoped1 = std::move(scoped);
    return 0;
}
