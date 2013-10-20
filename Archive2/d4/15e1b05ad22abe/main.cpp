#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <list>

template<
  typename wrapped_iterator_t,
  typename value_type = typename std::iterator_traits<wrapped_iterator_t>::value_type
>
struct value_iterator
  : std::iterator<typename std::iterator_traits<wrapped_iterator_t>::iterator_category, value_type>
{
  value_iterator (wrapped_iterator_t it)
    : _it (it)
  { }

  value_iterator (wrapped_iterator_t it, value_type const& value)
    : _it (it), _value (value)
  { }

  value_type& operator* () { return _value = *_it; }

  value_iterator& operator++ ()    { _value = *(++_it);                              return *this; }
  value_iterator  operator++ (int) { value_iterator copy (*this); _value = *(++_it); return  copy; }

  bool operator== (value_iterator const& rhs) {
    return _it == rhs._it || _value == rhs._value;
  }

  bool operator!= (value_iterator const& rhs) {
    return ! this->operator== (rhs);
  }

  wrapped_iterator_t _it;
  value_type      _value; /* boost::optional */
};

template<typename It>
value_iterator<It> make_value_iterator (It const& iterator) {
  return { iterator };
}

template<typename It, typename T>
value_iterator<It> make_value_iterator (It const& iterator, T const& value) {
  return { iterator, value };
}

void
test_the_shiznit (std::string const& test_data)
{
  std::istringstream iss (test_data);
  std::vector<int> vec;

  std::copy (
    make_value_iterator (std::istream_iterator<int> (iss)),
    make_value_iterator (std::istream_iterator<int> (), 0),
    std::back_inserter (vec)
  );

  std::cerr << "[ ";
  for (auto val : vec) std::cerr << val << " ";
  std::cerr << "]\n";
}

int
main (int argc, char *argv[])
{
  test_the_shiznit ("1 2 3 4 0 5 6 7");
  test_the_shiznit ("1 2 3 4 5 6 7 8");

  std::list<int> lst = { 1, 2, 3, 4, 5, 6 };

  size_t offset_of_3 = std::distance (
    make_value_iterator (lst.begin ()),
    make_value_iterator (lst.end (), 3)
  );

  std::cerr << "offset of 3 in `lst`: " << offset_of_3 << "\n";
}