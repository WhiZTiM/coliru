#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename Grammar>
bool check(Grammar const& g, std::string const& input, qi::unused_type) {
    auto f = input.begin(), l = input.end();
    try {
        return qi::parse(f, l, g);
    } catch(...) {
        return false;
    }
}

template <typename Grammar, typename Skipper>
bool check(Grammar const& g, std::string const& input, Skipper const& s) {
    auto f = input.begin(), l = input.end();
    try {
        return qi::phrase_parse(f, l, g, s);
    } catch(...) {
        return false;
    }
}

#define REPORT(g, i, s, expect) do { assert(expect == check(g, i, s)); } while(0)
#define SHOULD_WORK(g, i, s) REPORT(g, i, s, true)
#define SHOULD_FAIL(g, i, s) REPORT(g, i, s, false)

template <typename Skipper = qi::unused_type>
void do_all_tests(Skipper const& s = Skipper()) {

    auto A = qi::copy(qi::char_("$_") | qi::alpha);
    auto B = qi::copy(qi::char_("z"));

    // using skipper:
    SHOULD_WORK(A >> B , "$z", s);
    SHOULD_FAIL(A >> B , "$.", s);
    SHOULD_FAIL(A >> B , "$" , s);

    SHOULD_WORK(A  > B , "$z", s);
    SHOULD_FAIL(A  > B , "$.", s);
    SHOULD_FAIL(A  > B , "$" , s);

    // positive assertion (does not consume B)
    SHOULD_WORK(A >> &B, "$z", s);
    SHOULD_FAIL(A >> &B, "$.", s);
    SHOULD_FAIL(A >> &B, "$" , s);

    SHOULD_WORK(A  > &B, "$z", s);
    SHOULD_FAIL(A  > &B, "$.", s);
    SHOULD_FAIL(A  > &B, "$" , s);

    // negative assertion:
    SHOULD_FAIL(A >> !B, "$z", s);
    SHOULD_WORK(A >> !B, "$.", s);
    SHOULD_WORK(A >> !B, "$" , s);

    SHOULD_FAIL(A  > !B, "$z", s);
    SHOULD_WORK(A  > !B, "$.", s);
    SHOULD_WORK(A  > !B, "$" , s);

}

int main() {
    do_all_tests(qi::unused); // no skipper
    do_all_tests(qi::space);
    std::cout << "All tests succeeded\n";
}
