#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>    
#include <sstream>
#include <type_traits>
#include <memory>
#include <tuple>
#include <cstddef>
#include <algorithm>

    template<class...>struct types{using type=types;};
    template<class T>struct tag{using type=T;};
    template<class Tag>using type_t=typename Tag::type;
    template<std::size_t i>struct index:std::integral_constant<std::size_t, i>{};

    template<class T, class Types>struct index_of{};
    template<class T, class Types>using index_of_t=type_t<index_of<T,Types>>;

    template<class T, class...Ts>struct index_of<T, types<T,Ts...>>:
      tag< index<0> >
    {};
    template<class T, class T0, class...Ts>struct index_of<T, types<T0, Ts...>>:
      tag< index< index_of_t<T,types<Ts...>>::value+1 > >
    {};

    using token = std::shared_ptr<void>;
    template<class M>
    struct broadcaster {
      using f = std::function< void(M) >;
      std::vector<std::weak_ptr<f>> listeners;
      token reg( f target ) {
        // if thread safe, (write)lock here
        auto sp = std::make_shared<f>(std::move(target));
        listeners.push_back( sp );
        return sp;
        // unlock here
      }
      void trim() {
        // if thread safe, (write)lock here
        auto it = std::remove_if( listeners.begin(), listeners.end(), [](auto&& p){
          return p.expired();
        } );
        listeners.erase( it, listeners.end() );
        // unlock here
     }
      void send( M m ) {
        trim(); // remove dead listeners
        // (read) lock here
        auto tmp_copy = listeners; // copy the listeners, just in case
        // unlock here

        for (auto w:tmp_copy) {
          auto p = w.lock();
          if (p) (*p)(m);
        }
      }
    };

    template<class...Ts>
    struct subject {
      std::tuple<broadcaster<Ts>...> stations;
      template<class M>
      broadcaster<M>& station() {
        return std::get< index_of_t<M, types<Ts...>>::value >( stations );
      }
      template<class M>
      token reg( std::function<void(M)> listener ) {
        return station<M>().reg(std::move(listener));
      }
      template<class M>
      void send( M m ) {
        station<M>().send(std::forward<M>(m));
      }
    };

int main() {
    std::cout << "Test beings:\n";
    subject<int, std::string const&> s;
    auto t0 = s.reg<int>([](int x){std::cout << "hello #" << x << "\n"; });
    auto t1 = s.reg<std::string const&>([](std::string const& s){std::cout << "hello \"" << s << "\"\n"; });
    s.send<int>(3);
    s.send<std::string const&>("world");
    t1 = {};
    s.send<std::string const&>("universe");
    auto t2 = s.reg<int>([](int x){std::cout << "#" << x << " says hello\n"; });
    s.send<int>(2);
    t0 = {};
    s.send<int>(1);
    t2 = {};
    s.send<int>(0);
}