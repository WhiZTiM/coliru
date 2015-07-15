#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_istream_iterator.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/support_look_ahead.hpp>

int main()
{
    namespace qi = boost::spirit::qi;
    using qi::parse;
    using qi::byte_;
    using qi::int_;
    
    std::istringstream ss{"123456789"};
    
    using Iterator = boost::spirit::look_ahead<std::istream_iterator<char>,256>;
    
    auto f = Iterator{std::istream_iterator<char>{ss}};
    auto l = Iterator{};
    
    auto match = [](auto ...){
        std::cout << "match" << std::endl;
    };

    parse(f,l, byte_('1')[match]);
    parse(f,l, byte_('2')[match]);
    
    std::cout << *f << ss.rdbuf() << std::endl;
    
    
    
    return 0;
}
