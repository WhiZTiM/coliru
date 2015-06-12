    #include <iostream>
    #include <string>
    #include <boost/spirit/include/qi.hpp>
    #include <boost/phoenix.hpp>
    #include <boost/lexical_cast.hpp>
    using namespace boost::spirit;

struct to_string_ {
    using result_type = std::string;
    template<class T>
    std::string operator()(const T& arg) const { return boost::lexical_cast<std::string>(arg); }
};

boost::phoenix::function<to_string_> to_string;

    template <typename Iterator>
    struct z3_exp_grammars : qi::grammar<Iterator, std::string(), ascii::space_type>
    {
        z3_exp_grammars() : z3_exp_grammars::base_type(text)
        {
            text = qi::int_[qi::_val = to_string(qi::_1)];
        }

        qi::rule<Iterator, std::string(), ascii::space_type> text;

    };


    int main(){

        std::string test("3");
            std::string result;
            std::string::const_iterator beg = test.begin();
            std::string::const_iterator end = test.end();
            typedef z3_exp_grammars<std::string::const_iterator> z3_exp_grammars;
            z3_exp_grammars par;
            qi::phrase_parse(beg,end,par,ascii::space, result);
            std::cout<<"Result is "<<result<<std::endl;
}
