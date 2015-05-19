#include <boost/variant.hpp>

#include <iostream>

// Note: no inheritance from common base
struct D1
{
  void hello () const
  {
    std::cout << "Hello from D1" << std::endl;
  }
};

struct D2
{
  void hello () const
  {
    std::cout << "Hello from D2" << std::endl;
  }
};

struct Variant
{
  Variant () = default;

  template <typename T>
  explicit Variant (T &&t) : m_variant (std::forward<T> (t)) { }

  void hello () const
  {
    boost::apply_visitor (CallHelloVisitor (), m_variant);
  }

private:
  struct CallHelloVisitor : public boost::static_visitor<void>
  {
    template <typename T>
    void operator () (const T &t) const
    {
      t.hello ();
    }
  };

  boost::variant<D1, D2> m_variant;
};

int main ()
{
  Variant v;
  v.hello ();
}
