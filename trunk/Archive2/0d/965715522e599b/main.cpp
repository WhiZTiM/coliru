#if ((__cplusplus >= 201103L) || (_MSC_VER >= 1600)) && !defined(__clang__)
#    include <memory>
  template<typename T>
    using auto_ptr = std::unique_ptr<T>;
#elif defined(__clang__)
#   if (__has_include(<tr1/memory>))
#      include <tr1/memory>
  using std::auto_ptr;
#   endif
#elif (__cplusplus < 201103L)
#   include <tr1/memory>
  using std::auto_ptr;
#else
#   include <memory>
  template<typename T>
    using auto_ptr = std::unique_ptr<T>;
#endif

int main()
{
    auto_ptr<int> p;
    auto_ptr<int> pp;
}
