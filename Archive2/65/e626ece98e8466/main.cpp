#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/make_shared.hpp>

namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;
namespace ascii   = boost::spirit::ascii;

struct Bar {
    Bar(int y) { this->x = y; }
    ~Bar() {}

    int x;
};

struct Foo {
    using PBar = boost::shared_ptr<Bar>;
    Foo(PBar bar = {}) : _bar(bar) {}

    void DoStuff() { std::cout << _bar->x << std::endl; }

  private:
    PBar _bar;
};

template <typename Iterator>
struct TestGrammar : qi::grammar<Iterator, Foo(), ascii::space_type>
{
    TestGrammar() : TestGrammar::base_type(foo)
    {
        using namespace qi;
        foo = bar     [ _val = phoenix::construct<Foo::PBar>(_1) ] ;
        bar = double_ [ _val = phoenix::new_<Bar>(_1)      ] ;
    }

    qi::rule<Iterator, Foo(), ascii::space_type> foo;
    qi::rule<Iterator, Bar*(), ascii::space_type> bar;
};

int main() {
    std::string input;
    std::getline(std::cin, input);

    using It = std::string::const_iterator;
    It iter = input.begin();
    It end = input.end();

    TestGrammar<It> grammar;
    Foo f;
    bool result = qi::phrase_parse(iter, end, grammar, ascii::space, f);

    if (result) {
        //State s;
        f.DoStuff();
    } else {
        std::cout << "No Match!" << std::endl;
    }
}
