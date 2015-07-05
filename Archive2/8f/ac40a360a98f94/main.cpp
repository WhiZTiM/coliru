//#define BOOST_SPIRIT_DEBUG
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

#define EIGEN_INITILIZE_MATRICIES_BY_NAN
#include <Eigen/Eigen>
#include <limits>

template <typename Column, typename Skalar> class DataSet {

  public:
    using Matrix = Eigen::Matrix<Skalar, Eigen::Dynamic, Eigen::Dynamic>;

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
    (BOOST_FUSION_ADAPT_AUTO, mat) //(DataSet<Column, Skalar>::Matrix, mat) // TODO TRY this
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
            // << grammar should parse to DataSet ( add Column to vector, read matrix to eigen )
        {
            using namespace qi;
#if 0
#endif
            namespace px = boost::phoenix;

            auto col_ = px::bind(&Type::col, _val);

            start_  = header_ >> eol >> table_(px::size(col_));
            header_ = *name_;
            name_   = '"' >> +(char_ - '"') >> '"';

            {
                _r1_type number_of_columns; // expected

                table_  = *(row_(number_of_columns) [ do_append(_val, _1) ] >> eol);
                row_    = repeat(number_of_columns) [ auto_ ];
            }

            BOOST_SPIRIT_DEBUG_NODES(
                    (start_)(header_)(name_)
                    (table_)(row_)
                )
        }

      private:
        using Mat    = typename Type::Matrix;
        using Skalar = typename Mat::Scalar;

        struct do_append_f {
            template <typename M, typename V> struct result { typedef void type; };

            template <typename M, typename V>
            void operator()(M& matrix, V const& row) const {
                // resize matrix to add a row
                if (matrix.cols() == 0)
                {
                    matrix.resize(1, row.size());
                }
                else 
                {
                    matrix.conservativeResize(matrix.rows()+1, matrix.cols());
                    assert(row.size() == matrix.cols());
                }

                // fill the row
                for (size_t colidx = 0; colidx < matrix.cols(); ++colidx)
                {
                    matrix(matrix.rows()-1, colidx) = row[colidx];
                }
            }
        };
        boost::phoenix::function<do_append_f> do_append;

        qi::rule<It, Type()                     , Skipper> start_;
        qi::rule<It, Mat(size_t)                , Skipper> table_;
        qi::rule<It, std::vector<Skalar>(size_t), Skipper> row_;
        qi::rule<It, std::vector<Column>()      , Skipper> header_;
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

    return 0;
}
