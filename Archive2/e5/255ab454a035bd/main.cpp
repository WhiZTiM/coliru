template<typename T> struct type_ { typedef T type; };

template <class... Ts>
using last_element = decltype(type_<Ts>...)::type;

