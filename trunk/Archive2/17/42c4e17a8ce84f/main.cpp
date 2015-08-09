#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>

    namespace adl_aux {
      using std::begin; using std::end;
      template<class R>
      auto adl_begin(R&&)->decltype(begin(std::declval<R>()));
      template<class R>
      auto adl_end(R&&)->decltype(end(std::declval<R>()));
    }
    template<class R>
    using adl_begin = decltype(adl_aux::adl_begin(std::declval<R>()));
    template<class R>
    using adl_end = decltype(adl_aux::adl_end(std::declval<R>()));

    template<class R>using iterator_t = adl_begin<R>;
    template<class R>using value_t = std::remove_reference_t<decltype(*std::declval<iterator_t<R>>())>;

    template<class R, class T, class F=std::less<T>>
    value_t<R>* bin_search( R&& r, T&& t, F&& f={} ) {
      using std::begin; using std::end;
      auto range = std::equal_range( begin(r), end(r), std::forward<T>(t), std::forward<F>(f) );
      if (range.first==range.second) return nullptr;
      return std::addressof( *range.first );
    }

    template<class F, class C>
    struct order_by_t : private F, private C {
      F const& f() const { return *this; }
      C const& c() const { return *this; }
      template<class T>
      auto f(T&&t) const ->decltype( std::declval<F const&>()(std::declval<T>()) ) {
        return f()(std::forward<T>(t));
      }
      template<class T, class... Unused>
      auto f(T&&t, Unused&&... ) const
      -> std::decay_t<T>
      {
        return std::forward<T>(t);
      }
      template<class Lhs, class Rhs>
      bool operator()(Lhs&& lhs, Rhs&& rhs) const {
        return c()( f(std::forward<Lhs>(lhs)), f(std::forward<Rhs>(rhs)) );
      }
      template<class F0, class C0>
      order_by_t( F0&& f_, C0&& c_ ):
        F(std::forward<F0>(f_)), C(std::forward<C0>(c_))
      {}
    };
    template<class C=std::less<>, class F>
    auto order_by( F&& f, C&& c={} )
    -> order_by_t<std::decay_t<F>, std::decay_t<C>>
    { return {std::forward<F>(f), std::forward<C>(c)}; }

struct Person {
    std::string name;
    Person (const std::string& n) : name(n) {}
    std::string getName(int, char) const {return name;}  // int, char play no role in this
        // simple example, but let's suppose that they are needed.
} *Bob = new Person("Bob"), *Frank = new Person("Frank"), *Mark = new Person("Mark"),
    *Tom = new Person("Tom"), *Zack = new Person("Zack");

const std::vector<Person*> people = {Bob, Frank, Mark, Tom, Zack};

int main() {
   auto ordering = order_by(
      [](Person const* p)
        {return p->getName(5,'a');}
   );
   Person*const* p = bin_search( people, "Tom", ordering );
   std::cout << p << " " << *p << "\n";
   if (p && *p)
       std::cout << (*p)->getName(5, 'a') << '\n';
}
