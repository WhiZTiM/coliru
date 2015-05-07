#include <boost/mpl/at.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/vector.hpp>
#include <type_traits>
 

int main()
{
    using namespace boost::mpl;

    using v = vector<int, bool>;
    
    using v_plus_char = push_back<v, char>::type;
    
    static_assert(std::is_same<at<v_plus_char, int_<0>>::type, int>{});
    static_assert(std::is_same<at<v_plus_char, int_<1>>::type, bool>{});
    static_assert(std::is_same<at<v_plus_char, int_<2>>::type, char>{});
    
    static_assert(size<v_plus_char>::value == 3);
}
