#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>

int main() {
    std::vector<std::string> components;
    boost::split(components, "", boost::is_any_of(","), boost::algorithm::token_compress_on);
    
    assert(components.size() == 0);
}