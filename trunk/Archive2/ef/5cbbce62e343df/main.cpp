#include <type_traits>

template<typename Cond>
using enable_if = std::enable_if_t<Cond::value, int>;

template<typename Arg, enable_if<std::is_integral<Arg>> = 0, enable_if<std::is_signed<Arg>> = 0>
void fine(Arg) {}

template<typename Arg, enable_if<std::is_integral<Arg>> = 0, enable_if<std::is_unsigned<Arg>> = 0>
void fine(Arg) {}

/* error: redefinition of 'template<class Arg, class, class> void uhoh(Arg)'
template<typename Arg, typename = enable_if<std::is_integral<Arg>>, typename = enable_if<std::is_signed<Arg>>>
void uhoh(Arg) {}

template<typename Arg, typename = enable_if<std::is_integral<Arg>>, typename = enable_if<std::is_unsigned<Arg>>>
void uhoh(Arg) {}
*/

int main()
{
    fine(0);
    fine(0u);
}
