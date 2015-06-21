#include <iostream>
#include <string>
#include <boost/regex.hpp>
using namespace std;
using namespace boost;
int main() {
    regex rule("(?<test>\\d+)");
    string str = "11.22.33.44";
    boost::smatch result;
    string::const_iterator start = str.begin();
    string::const_iterator end = str.end();
    while (regex_search(start, end, result, rule)) {
        std::cout << result["test"].str() << std::endl;
        start = result["test"].second;
    }
}
