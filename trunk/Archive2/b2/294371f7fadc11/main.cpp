#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <iostream>
#include <iomanip>

namespace qi = boost::spirit::qi;
namespace vec = boost::fusion;

struct student_t {
    std::string matr_nr;
    unsigned    points;
    int         mark;
};

struct date_t {
    unsigned dd, mm, yyyy;

    friend std::ostream& operator<<(std::ostream& os, date_t const& d) {
        std::ostream local(os.rdbuf());
        local << std::setw(2) << std::setfill('0') << d.dd <<
            "-" << std::setw(2) << std::setfill('0') << d.mm <<
            "-" << std::setw(4) << std::setfill('0') << d.yyyy;
        return os;
    }
};

BOOST_FUSION_ADAPT_STRUCT(student_t,
        (std::string,matr_nr)(unsigned,points)(int,mark))
BOOST_FUSION_ADAPT_STRUCT(date_t,
        (unsigned,dd)(unsigned,mm)(unsigned,yyyy))

struct klausur {
    std::string str_subject;
    std::string str_dozent;
    date_t date;

    unsigned count;
    std::vector<student_t>   students;

    friend std::ostream& operator<<(std::ostream& os, klausur const& k)
    {
        os << "Fach: "   << k.str_subject << '\n';
        os << "Dozent: " << k.str_dozent  << '\n';
        os << "Datum: "  << k.date        << '\n';
        os << "Anzahl: " << k.count       << '\n';
        for (auto& s : k.students) {
            os << "Mat_Nr: " << s.matr_nr << '\n';
            os << "Punkte: " << s.points  << '\n';
            os << "Note: "   << s.mark    << '\n';
        }
        return os;
    }
};

BOOST_FUSION_ADAPT_STRUCT(klausur,
        (std::string                     , str_subject)
        (std::string                     , str_dozent)
        (date_t                          , date)
        (unsigned                        , count)
        (std::vector<student_t>          , students)
    )

template <typename Iterator, typename Skipper = qi::ascii::blank_type>
struct grammar : qi::grammar<Iterator, klausur(), Skipper> {
    grammar() : grammar::base_type(start) {
        using namespace qi;
        subject   = "Fach:"   >> lexeme [ +~char_('\n') ] >> eol;
        dozent    = "Dozent:" >> lexeme [ +~char_('\n') ] >> eol;
        date      = "Datum:"  >> lexeme [uint_ >> '-' >> uint_ >> '-' >> uint_] >> eol;
        count     = "Anzahl:" >> uint_ >> eol;
        points    = uint_;
        mark      = int_parser<int, 10, 1, 1>(); // single base-10 digit

        // no clue about this format; what is it? Just a real number?
        matnumber = lexeme[digit >> digit >> digit >> punct >> digit >> digit >> digit];

        student   = matnumber >> points >> mark;

        _a_type expected;
        klausur_ %= subject
                 >> dozent
                 >> date
                 >> count            [ expected = _1, std::cout << _1 << " expected: " << expected << "\n"  ]
                 >> repeat(expected) [ student >> (eol|eoi) ]
                 ;

        start     = klausur_;

        BOOST_SPIRIT_DEBUG_NODES((start)(klausur_)(student)(matnumber)(mark)(points)(count)(date)(dozent)(subject))
    }

  private:
    qi::rule<Iterator, klausur(), Skipper> start;
    qi::rule<Iterator, klausur(), Skipper, qi::locals<unsigned> > klausur_;

    qi::rule<Iterator, std::string()    , Skipper> subject;
    qi::rule<Iterator, std::string()    , Skipper> dozent;
    qi::rule<Iterator, date_t(),          Skipper> date;
    qi::rule<Iterator, unsigned()       , Skipper> count;
    qi::rule<Iterator, std::string()    , Skipper> matnumber;
    qi::rule<Iterator, unsigned()       , Skipper> points;
    qi::rule<Iterator, int()            , Skipper> mark;
    qi::rule<Iterator, student_t()      , Skipper> student;
};

int main() {
    using It = std::string::const_iterator;
    std::string const input =
R"(Fach: Physics
Dozent: Wayne
Datum: 20-10-2014
Anzahl: 2
729.888 33  5
185.363 35  5)";

    It f = input.begin(), l = input.end();

    grammar<It> g;
    klausur k;
    bool ok = qi::phrase_parse(f, l, g, qi::ascii::blank, k);

    if (ok) {
        std::cout << "Parse success\n";
        std::cout << k;
    } else {
        std::cout << "Parse failed\n";
    }

    if (f!=l) {
        std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
    }
}
