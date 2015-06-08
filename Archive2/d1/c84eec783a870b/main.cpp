#include <cstdint>
#include <type_traits>
#include <functional>
#include <vector>
#include <tuple>
#include <iostream>
#include <atomic>
#include <algorithm>
#include <set>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/fusion/include/std_tuple.hpp>

using namespace std;

template<typename Op,typename ...Ts>
class Observable{
public:
    Observable()
    : idGen_{0} {};

    template<typename T>
    Op& on(std::function<void(T)>&& f)
    {
        FunctionWrapper<T> fw{0,std::move(f)};
        get<T>().subscribe(std::move(fw));
        return static_cast<Op&>(*this);
    }

    template<typename OutIter,typename T>
    Op& on(OutIter idIt,std::function<void(T)>&& f)
    {
        auto id = ++idGen_;
        idIt = id;
        FunctionWrapper<T> fw{id,std::move(f)};
        get<T>().subscribe(std::move(fw));
        return static_cast<Op&>(*this);
    }

    template<typename T>
    Op& notify(const T& value)
    {
        get<T>().notify(value);
        return static_cast<Op&>(*this);
    }

    void unsubscribe(size_t id)
    {
        boost::fusion::for_each(observables_,[id](auto & observable)
        {
            observable.unsubscribe(id);
        });
    }

private:
    //wrapper to makes function comparable
    template<typename T>
    struct FunctionWrapper
    {
        FunctionWrapper(size_t id,std::function<void(T)>&& f)
        : id_{id},f_{std::move(f)} {}

        FunctionWrapper(FunctionWrapper<T>&& other)
        : id_{other.id_},f_{std::move(other.f_)}
        {
            other.id_ = std::numeric_limits<size_t>::max();
        }

        bool operator < (FunctionWrapper<T> const& other) const
        {
            return id_ < other.id_;
        }

        size_t id_;
        std::function<void(T)> f_;
    };

    template<typename T>
    struct ObservableImpl
    {
        void subscribe(FunctionWrapper<T>&& f)
        {
            observers_.emplace_back(std::move(f));
        }

        void unsubscribe(size_t id)
        {
//            observers_.erase(
//                    std::remove_if(std::begin(observers_),std::end(observers_),
//                                   [id](auto const& f) {return f.id_ == id;}),
//                    std::end(observers_));
            observers_.erase(std::begin(observers_),std::end(observers_));
        }

        void notify(T const& value)
        {
            //TODO catch exceptions
            for(auto& o : observers_)
            {
                o.f_(value);
            }
        }

    private:
        std::set<FunctionWrapper<T>> observers_;
    };

    using Observables = std::tuple<ObservableImpl<Ts>...>;
    using Types = boost::mpl::vector<Ts...>;

    template<typename T>
    auto& get()
    {
        using iter = typename boost::mpl::find<Types,T>::type;
        return std::get<iter::pos::value>(observables_);
    }

    std::atomic<size_t> idGen_;
    Observables observables_;
};



struct FrameReceived{};
struct Frame{};

class IHostMediaAccessControl : public Observable<IHostMediaAccessControl,FrameReceived>
{
public:
    void onSendFrame(Frame&& frame)
    {
        cout << "Send Frame Call" << endl;
    };
};


template<std::uint8_t Id, typename R>
class Generic : public Observable<Generic<Id,R>,R>
{
public:
    using ReturnType = R;

    Generic(IHostMediaAccessControl& hmac) : hmac_{hmac}
    {
        auto ids = std::back_inserter(ids_);
        using Ids = decltype(ids);

        hmac_.on<Ids,FrameReceived>(ids,[this](auto const& event)
        {
            this->notify(R{}); // <--- na razie wystarczy tylko tyle
        });
    }

    ~Generic()
    {
        for(auto id : ids_)
        {
            hmac_.unsubscribe(id);
        }
    }

    template<typename FusionSequence>
    void operator()(const FusionSequence& sequence)
    {
        std::vector<std::uint8_t> payload{};
        payload.push_back(Id);
        boost::fusion::for_each(sequence, [&payload](const auto& v)
        {
            //using Fibaro::serialize; // <--- customization point
            //serialize(std::back_inserter(payload), v);
        });
        payload.push_back(1); // <--- function identifier, na razie wystarczy stała "1"


        //hmac_.onSendFrame(SofFrame{SofFrame::Type::Request,std::move(payload)});
    }

private:
    IHostMediaAccessControl& hmac_;
    std::vector<std::size_t> ids_;
};

int main(int argc, char* argv[])
{
    IHostMediaAccessControl hmac;
    Generic<1,size_t> req(hmac);


    return 0;
}
