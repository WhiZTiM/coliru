#include <iostream>
#include <memory>

namespace detail
{
    template<typename T, typename _arg>
    struct is_shared_ptr
    : std::is_same<std::decay_t<_arg>,
                   std::shared_ptr<T>
                  >
    {};
}

template<typename _type>
class handle
{
  using ptr = std::shared_ptr<_type>;
  using pptr = std::shared_ptr<ptr>;
public:
  handle() :
    mData(make_pptr())
  {}
  
  handle(handle<_type> const & other) :
    mData(make_pptr(*(other.mData)))
  {}
  
  handle(_type && data) :
    mData(make_pptr(std::move(data)))
  {}
  
  template<typename ..._args>
  constexpr auto make_ptr(_args && ...args)
  {
    return std::make_shared<_type>(std::forward<_args>(args)...);
  }

  constexpr auto make_pptr(ptr const & pointer)
  {
    return std::make_shared<ptr>(pointer);
  }
  
  template<typename _arg,
           typename = std::enable_if_t<
                        not detail::is_shared_ptr<_type, _arg>::value
                      >
          >
  constexpr auto make_pptr(_arg && arg)
  {
    return std::make_shared<ptr>(make_ptr(std::forward<_arg>(arg)));
  }

  template<typename ..._args,
           typename = std::enable_if_t<sizeof...(_args) != 1>
          >
  constexpr auto make_pptr(_args && ...args)
  {
    return std::make_shared<ptr>(make_ptr(std::forward<_args>(args)...));
  }

private:
  pptr mData;
};

struct foo
{
    foo() = default;
    foo(int) {}
    foo(std::shared_ptr<foo>, int) {}
};

int main()
{
  handle<int> h = 5;
  handle<int> h2(h);
  handle<int> h3;
  
  handle<foo>{}.make_pptr();
  handle<foo>{}.make_pptr(42);
  handle<foo>{}.make_pptr(std::shared_ptr<foo>{}, 42);
}
