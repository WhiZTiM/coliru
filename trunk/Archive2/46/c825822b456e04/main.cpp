// simple demo coming up.
// parse competing date formats with varying field orders the dumb way (I mean, not using a proper library)
//
//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <iomanip>

namespace qi = boost::spirit::qi;

namespace ast { // conventional naming
    struct target_date {
        int day, month, year;
    };

    struct line_record {
        target_date date;
        double x, y;
    };

    static inline std::ostream& operator<<(std::ostream& os, target_date const& td) {
        // good habit of the day: separate stream state
        std::ostream wrap(os.rdbuf());
        wrap << std::setfill('0')
            << std::setw(4) << td.year << "/"
            << std::setw(2) << td.month << "/"
            << std::setw(2) << td.day;
        
        return os;
    }

    static inline std::ostream& operator<<(std::ostream& os, line_record const& lr) {
        return os << lr.date << " " << lr.x << " " << lr.y; // not bothering about precision on the doubles
    }
}

BOOST_FUSION_ADAPT_STRUCT(ast::line_record,
        (ast::target_date, date)(double,x)(double,y))

BOOST_FUSION_ADAPT_STRUCT_NAMED(ast::target_date,
        yyyymmdd_date_,
        (int,year)(int,month)(int,day))

BOOST_FUSION_ADAPT_STRUCT_NAMED(ast::target_date,
        ddmmyyyy_date_,
        (int,day)(int,month)(int,year))

namespace ast {
    using boost::fusion::adapted::yyyymmdd_date_;
    using boost::fusion::adapted::ddmmyyyy_date_;
}

template <typename It, typename Skipper = qi::blank_type>
struct parser : qi::grammar<It, ast::line_record(), Skipper>
{
    parser() : parser::base_type(start) {
        using namespace qi;

        start = any_date >> double_ >> double_;

        any_date = yyyymmdd | ddmmyyyy;

        static const qi::int_parser<int, 10, 4, 4> _4digits = {};
        static const qi::int_parser<int, 10, 2, 2> _2digits = {};

        yyyymmdd  = _4digits >> '/' >> _2digits >> '/' >> _2digits;
        ddmmyyyy  = _2digits >> '.' >> _2digits >> '.' >> _4digits;

        BOOST_SPIRIT_DEBUG_NODES((start)(any_date)(yyyymmdd)(ddmmyyyy))
    }

  private:
    qi::rule<It, ast::line_record(),    Skipper> start;
    qi::rule<It, ast::target_date(),    Skipper> any_date;
    qi::rule<It, ast::yyyymmdd_date_(), Skipper> yyyymmdd;
    qi::rule<It, ast::ddmmyyyy_date_(), Skipper> ddmmyyyy;
};

int main() {
    // OP was reading from a file, IIRC
    std::istringstream iss("2015/03/14 3.5 4.3\n14.03.2015 3.5 4.3"); // streams are more realistic. 
    iss.unsetf(std::ios::skipws); // PITFALL #1 in spirit stream parsing.

    using It = boost::spirit::istream_iterator;
    parser<It> p; // sue me for short names
    It f(iss), l; // I like: `It f(iss >> std::noskipws), l;` but it's kinda obscure

    std::vector<ast::line_record> parsed;
    bool ok = qi::phrase_parse(f, l, p % +qi::eol, qi::blank, parsed); // that's spirit magic

    if (ok) {
        std::cout << "Parse success: " << parsed.size() << " lines\n";

        for (auto const& r : parsed)
            std::cout << r << "\n";
    } else {
        std::cout << "parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed: '" << std::string(f,l) << "'\n";
}
