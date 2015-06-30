#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <utility>
#include <iterator>

using namespace std;

template< class T,
          class CharT = char,
          class Traits = std::char_traits<CharT> >
class ostreambin_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void> {
public:
    typedef CharT char_type;
    typedef Traits traits_type;
    typedef std::basic_ostream<CharT, Traits> ostream_type;

protected:
    ostream_type& stream_;

public:
    ostreambin_iterator(ostream_type& stream) : stream_(stream) { }

    ostreambin_iterator& operator=(T const& value) 
    {
        stream_.write(reinterpret_cast<const char*>(&value), sizeof(T));
        return *this;
    }
 
    ostreambin_iterator& operator*() { return *this; }
    ostreambin_iterator& operator++() { return *this; }
    ostreambin_iterator& operator++(int) { return *this; }
};

int main() {
  std::vector<long> d(3);
  d[0] = 0x30;
  d[1] = 0x31;
  d[2] = 0x32;

  ostreambin_iterator<long> out(cout);

cout << "begin" << endl;
  copy(std::begin(d), std::end(d), out);
  cout << endl;
  cout << "end" << endl;
} 