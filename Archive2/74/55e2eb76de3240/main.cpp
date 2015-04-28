#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <map>

template<std::size_t idx = 0, typename ...T>
inline typename std::enable_if<idx == sizeof...(T), void>::type
cat_tuple(std::tuple<T...> const& t, std::stringstream &s){
}

template<std::size_t idx = 0, typename ...T>
inline typename std::enable_if<idx < sizeof...(T), void>::type
cat_tuple(std::tuple<T...> const& t, std::stringstream &s){
    if (idx != 0)
        s << ",";
    s << std::get<idx>(t);
    cat_tuple<idx+1, T...>(t, s);
}

typedef std::tuple<int, int> my_tuple;
typedef std::map<my_tuple, int> my_map;
int main(){
    my_map m;
    my_tuple t(1, 2);
    m.insert(std::pair<my_tuple, int>(t, 1));
    std::stringstream s;
    for(my_map::iterator i = m.begin(); i != m.end(); ++i){
        if (i != m.begin())
            s << "\n";
        cat_tuple(i->first, s); //Substitution error, see below
        s << " " << i->second;
    }
    std::cout << s.str() << std::endl;
}
