#include <memory>

#if __cplusplus >= 201103L
# ifdef __clang__
#  if __has_include(<forward_list>)
// either using libc++ or a libstdc++ that's new enough to have unique_ptr
#   define HAVE_UNIQUE_PTR 1
#  endif
# else // not clang, assume unique_ptr available
#  define HAVE_UNIQUE_PTR 1
# endif
#endif

#ifdef HAVE_UNIQUE_PTR
template<typename T> using auto_ptr = std::unique_ptr<T>;
#else
using std::auto_ptr;
#endif

int main()
{
    auto_ptr<int> p;
    auto_ptr<int> pp;
}
