#include <boost/regex.hpp>
#include <iostream>

int main() {
    boost::cmatch what;
    std::string fn_re_str = R"(\.sig\|\|([a-zA-Z0-9$]+)\()";
    boost::regex fn_re(fn_re_str);
    if (boost::regex_search("{var d=a[c];if(d.sig||d.s){var e=d.sig||qt(d.", what, fn_re)) {
        std::cout << what[1] << std::endl;
    } else {
        std::cerr << "not found" << std::endl;
    }
}
