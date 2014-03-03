#include <regex>
#include <iostream>

using namespace std;

constexpr auto &text = R"(
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string1":"string2"XXXXXXXXXXXXXXXXXXXXXXXXXX"string3":"string4" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
XXXXXXXXXXXXXXXXXXXXXXXXXXXX"string5":"string6"XXXXXXXXXXXXXXXXXXXXXXXXXX"string7":"string8" XXXXXXXXXXXXXXXXXXXXXXXXXXXX...
)";

int main() {
    const regex pieces_regex{R"~("([^"]*)":"([^"]*)")~"};
    cmatch pieces_match;
    auto i = text;
    constexpr auto e = text + sizeof(text) - 1;
    while (regex_search(i, e, pieces_match, pieces_regex)) {
        cout << "First: " << pieces_match[1].str()
             << ", Second: " << pieces_match[2].str() << endl;
        i = pieces_match[0].second;
    }
}