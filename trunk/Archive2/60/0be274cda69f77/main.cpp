#include <iostream>
#include <utility>
#include <tuple>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <future>

template<class T>
struct synchronized {
  template<class F>
  auto read(F&& f) const&->std::result_of_t<F(T const&)> {
    return access(std::forward<F>(f), *this);
  }
  template<class F>
  auto read(F&& f) &&->std::result_of_t<F(T&&)> {
    return access(std::forward<F>(f), std::move(*this));
  }
  template<class F>
  auto write(F&& f)->std::result_of_t<F(T&)> {
    return access(std::forward<F>(f), *this);
  }
  // uses `const` ness of Syncs to determine access:
  template<class F, class... Syncs>
  friend auto access( F&& f, Syncs&&... syncs )->
  std::result_of_t< F(decltype(std::forward<Syncs>(syncs).t)...) >
  {
    return access2( std::index_sequence_for<Syncs...>{}, std::forward<F>(f), std::forward<Syncs>(syncs)... );
  };
  synchronized(synchronized const& o):t(o.read([](T const&o){return o;})){}
  synchronized(synchronized && o):t(std::move(o).read([](T&&o){return std::move(o);})){}  
  // special member functions:
  synchronized( T & o ):t(o) {}
  synchronized( T const& o ):t(o) {}
  synchronized( T && o ):t(std::move(o)) {}
  synchronized( T const&& o ):t(std::move(o)) {}
  synchronized& operator=(T const& o) {
    write([&](T& t){
      t=o;
    });
    return *this;
  }
  synchronized& operator=(T && o) {
    write([&](T& t){
      t=std::move(o);
    });
    return *this;
  }
private:
  template<class X, class S>
  static auto smart_lock(S const& s) {
    return std::shared_lock< std::shared_timed_mutex >(s.m, X{});
  }
  template<class X, class S>
  static auto smart_lock(S& s) {
    return std::unique_lock< std::shared_timed_mutex >(s.m, X{});
  }
  template<class L>
  static void lock(L& lockable) {
      lockable.lock();
  }
  template<class...Ls>
  static void lock(Ls&... lockable) {
      std::lock( lockable... );
  }
  template<size_t...Is, class F, class...Syncs>
  friend auto access2( std::index_sequence<Is...>, F&&f, Syncs&&...syncs)->
  std::result_of_t< F(decltype(std::forward<Syncs>(syncs).t)...) >
  {
    auto locks = std::make_tuple( smart_lock<std::defer_lock_t>(syncs)... );
    lock( std::get<Is>(locks)... );
    return std::forward<F>(f)(std::forward<Syncs>(syncs).t ...);
  }

  mutable std::shared_timed_mutex m;
  T t;
};
template<class T>
synchronized< T > sync( T&& t ) {
  return {std::forward<T>(t)};
}

int main() {
    auto scout = sync(std::ref(std::cout));
    
    
    std::vector< std::future<void> > world;
    for (auto c:"hello world") {
        world.push_back( std::async( std::launch::async, [&,c]{ scout.write([c](auto&&cout){
            cout.get() << c << '\n';
        }); } ) );
    }
    scout.write([](auto&& cout){
        cout.get() << "hello world\n";
    });
    for (auto&& fut:world)
        fut.get();
    std::cout << '\n';
    
}