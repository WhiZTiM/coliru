// #define BOOST_SPIRIT_DEBUG
// column.h
#ifndef _COLUMN__
#define _COLUMN__
#include <cstdio>
#include <iostream>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix.hpp>

struct Column {
    int         index;
    std::string name;
    std::string code;
};

//BOOST_FUSION_ADAPT_STRUCT(Column, (std::string, name)(std::string, code)(int, index))
BOOST_FUSION_ADAPT_STRUCT(Column, (std::string, name))

#endif

// dataset.h

#ifndef DATASET_H
#define DATASET_H

#include <boost/spirit/include/qi.hpp>

//#include "split.h"
#include <limits>
#include <armadillo>

// Let's use some Spirit magic fairy dust to convert vector<vector<T>> -> Mat<T>
//
// Because otherwise the grammar gets unwieldy/needing lots of Phoenix coding
namespace boost { namespace spirit { namespace traits {

    template <typename T>
        struct assign_to_attribute_from_value<arma::Mat<T>, std::vector<std::vector<T>> > {
            static void call(std::vector<std::vector<T> > const& exposed, arma::Mat<T>& attribute) {
                if (exposed.empty())
                    attribute.reset();

                attribute.set_size(exposed.size(), exposed.front().size()/*, arma::file_type::none*/);

                for (size_t col = 0; col < attribute.n_cols; ++col)
                for (size_t row = 0; row < attribute.n_rows; ++row)
                    attribute(row,col) = exposed.at(row).at(col);
            }
        };

} } }

template <typename Column, typename Skalar> class DataSet {
  public:
    using Matrix = arma::Mat<Skalar>;

    DataSet(){};
    DataSet(const int rows, const int cols) 
        : mat(rows, cols)
    {} 

  //private: // TODO change visibility?
    std::vector<Column> col;
    Matrix mat;
};

BOOST_FUSION_ADAPT_TPL_STRUCT(
    (Column)(Skalar),
    (DataSet) (Column)(Skalar),
    (std::vector<Column>, col)
    (BOOST_FUSION_ADAPT_AUTO, mat)
)

#endif

// grammar_std.h

#ifndef GRAMMAR_CSV_H
#define GRAMMAR_CSV_H

#include <boost/spirit/include/qi.hpp>

namespace {
    namespace qi = boost::spirit::qi;

    template <typename It, typename Type, typename Skipper = qi::blank_type>
    struct StdGrammar : qi::grammar<It, Type(), Skipper> {

        StdGrammar() : StdGrammar::base_type(start_, "StdGrammar") 
        {
            using namespace qi;
            namespace px = boost::phoenix;

            auto col_ = px::bind(&Type::col, _val);
            _a_type expect_rows;
            _r1_type no_rows;
            _r2_type no_cols;

            start_  = matrix_;
            matrix_ = omit [ uint_ [ expect_rows = _1 ] >> eol ]
                   >> header_ >> eol 
                   >> table_(expect_rows, px::size(col_))
                    ;
            header_ = *name_;
            name_   = '"' >> +(char_ - '"') >> '"';
            table_  = repeat(no_rows)[repeat(no_cols) [double_] >> eol];

            BOOST_SPIRIT_DEBUG_NODES((start_)(header_)(name_)(table_)(matrix_))
        }

      private:
        using Mat    = typename Type::Matrix;
        using Skalar = typename Mat::elem_type;
        using Tmp    = typename std::vector<std::vector<Skalar>>;

        qi::rule<It, Type(),                        Skipper> start_;
        qi::rule<It, Type(), qi::locals<size_t>,    Skipper> matrix_;
        qi::rule<It, Tmp(size_t rows, size_t cols), Skipper> table_;
        qi::rule<It, std::vector<Column>(),         Skipper> header_;

        // lexeme: no skipper
        qi::rule<It, std::string()> name_;
    };
}

#endif

// main file

#include <cstdio>
#include <iostream>

//#include "column.h"
//#include "dataset.h"
//#include "grammar_std.h"
#include <fstream>

int main() {
    using It = boost::spirit::istream_iterator;

    std::ifstream ifs("input.txt");
    It beg(ifs >> std::noskipws), end;

    DataSet<Column, float> ds;
    StdGrammar<It, DataSet<Column, float> > grammar;
    bool status = qi::phrase_parse(beg, end, grammar, qi::blank, ds);

    if (status) {
        std::cout << "Parse success\n";

        for(auto const& column : ds.col) std::cout << "Column: '" << column.name << "'\n";
         std::cout << ds.mat << "\n";
    } else {
        std::cout << "Parse failed\n";
    }

    if (beg!=end)
        std::cout << "Remaining input unparsed: '" << std::string(beg,end) << "'\n";
}
