template <typename T>
struct Wrapper
{
  decltype(auto) operator()() const
  {
    return m_t();
  }
  decltype(auto) operator()()
  {
    return m_t();
  }
  T m_t;
};

template <typename T>
auto make_wrapper(T t)
{
  return Wrapper<T>{t};
}


struct Foo
{
  int& operator()() {
    return x;
  }
  const int& operator()() const {
    return x;
  }
  int x;
};


int main()
{
  Foo foo;

  auto fun = [foo]() mutable -> decltype(auto) { return foo(); };
  auto wfun = make_wrapper(fun);
  const auto& cwfun = wfun;

  wfun();
  cwfun();
  
  return 0;
}
