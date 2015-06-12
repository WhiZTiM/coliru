#include <cstdlib> // Just to get the std::size_t
#include <type_traits>
#include <iterator>
#include <stdio.h>

template<typename Tp>
class forward_list {
  public:
    typedef std::size_t size_type;

    void assign(size_type n, const Tp& val)
    {
      printf("%s\n", __PRETTY_FUNCTION__);
    }

    template<typename InputIterator>
    typename std::enable_if<
        std::is_base_of<std::input_iterator_tag,
                        typename std::iterator_traits<InputIterator>::iterator_category
                       >::value
             >::type
        assign(InputIterator first, InputIterator last)
    {
      printf("%s\n", __PRETTY_FUNCTION__);
    }
};

int main()
{
  forward_list<int> l;
  l.assign(10, 5);
  return 0;
}
