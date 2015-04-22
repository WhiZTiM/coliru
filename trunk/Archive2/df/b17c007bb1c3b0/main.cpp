#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/noncopyable.hpp>

namespace qi      = boost::spirit::qi;
namespace phoenix = boost::phoenix;
namespace ascii   = boost::spirit::ascii;

struct Bar {
    Bar(int y) { this->x = y; }
    ~Bar() {}

    int x;
};

struct Foo {
    Foo(Bar *bar = 0) : _bar(bar) {}
    Foo(Foo const& o) : _bar(new Bar(*o._bar)) {}
    Foo& operator=(Foo const& o) { 
        Foo tmp;
        tmp._bar = new Bar(*o._bar);
        std::swap(tmp._bar, _bar);
        return *this;
    }

    ~Foo() { delete _bar; }

    void DoStuff() { std::cout << _bar->x << std::endl; }

  private:
    Bar *_bar;
};

template <typename Iterator>
struct TestGrammar : qi::grammar<Iterator, Foo(), ascii::space_type>
{
    TestGrammar() : TestGrammar::base_type(foo)
    {
        using namespace qi;
        foo = bar     [ _val = phoenix::construct<Foo>(_1) ] ;
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
