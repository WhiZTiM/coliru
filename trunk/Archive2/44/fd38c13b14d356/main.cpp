#include <iostream>
#include <regex>
#include <string>

int main()
{
    using std::cout;
    using std::endl;

    std::regex const pattern {"Monday"};
    std::string target {"Monday"};

    cout << "search pattern \"Monday\" on string \"" << target << "\"..." << endl;

    bool result1 = std::regex_match(target, pattern); // return true
    bool result2 = std::regex_search(target, pattern); // return false

    cout << std::boolalpha;
    cout << "result (match): " << result1 << endl;
    cout << "result (search): " << result2 << endl;

    return 0;
}
