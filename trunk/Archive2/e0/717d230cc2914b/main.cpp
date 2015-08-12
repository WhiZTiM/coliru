#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <functional>
#include <sstream>

namespace Jo_detail {
    std::stringstream stream;
}

template<class...Fs>
void run(Fs&&...fs) {
    using ex=int[];
    (void)ex{0, (
        std::forward<Fs>(fs)()
    , void(), 0)...};
}

template <class... Args>
std::string Jo(Args &&... args) {

    Jo_detail::stream.str("");

    run( [&]{Jo_detail::stream << std::forward<Args>(args);}... );

    // str() returns a copy anyway
    return Jo_detail::stream.str();
}
int main()
{
    std::cout << Jo( "hello", ' ', "world", '\n' );
}
