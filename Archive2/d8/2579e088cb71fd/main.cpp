// column.h

#ifndef _COLUMN__
#define _COLUMN__
#include <cstdio>
#include <iostream>
#include <string>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>

struct Column
{
 int index;
 std::string name;
 std::string code;
};

BOOST_FUSION_ADAPT_STRUCT( Column,
    		   (std::string, name  ),
			   (std::string, code  ),
			   (int        , index ))



#endif


// dataset.h

#ifndef DATASET_H
#define DATASET_H

#include <boost/spirit/include/qi.hpp>

#include "split.h"

#define EIGEN_INITILIZE_MATRICIES_BY_NAN
#include <Eigen/Eigen>

template< typename Column, typename Skalar>
class DataSet
{
 using Matrix = Eigen::Matrix< Skalar, Eigen::Dynamic, Eigen::Dynamic >;
 
public:

 DataSet()
 {
 };
 DataSet( const int rows, const int cols )
 {
  data.resize( rows, cols );
 }


private:
 std::vector< Column > col;
 Matrix mat;

};

#endif




// grammar_std.h

#ifndef GRAMMAR_CSV_H
#define GRAMMAR_CSV_H

#include <boost/spirit/include/qi.hpp>

namespace
{
 namespace qi = boost::spirit::qi;
 using Mat = std::vector< std::vector< float> >;
 
 template<typename It, typename Type >
 struct StdGrammar : qi::grammar< It, Type(), qi::space_type >
 {
  
  StdGrammar() : StdGrammar::base_type( start_, "StdGrammar" )      // <<<<< grammar should parse to DataSet ( add Column to vector, read matrix to eigen )
  {
   /*
     header_ = *( qi::lexeme['"' >> +(qi::char_ - '"') >> '"'][ ds->addColumn( qi::_1 )]  );
     table_  = *( qi::double_ %);
     start_ = header_ >> qi::eol >> table_ >> qi::eoi;
   */
  }
  
  
 private:
  qi::rule<It, Type()> start_;
  qi::rule<It> header_;
  qi::rule<It, Mat()> table_;
 };


};

#endif



// main file



#include <cstdio>
#include <iostream>

#include "column.h"
#include "dataset.h"
#include "grammar_std.h"

int main(int argc, char *argv[])
{
 DataSet<Column, float > ds;
 StdGrammar<std::string::iterator, DataSet > grammar;       // <<<< DataSet incomplete type ?


//  auto content{};
//  auto beg = content.begin();
//  auto end = content.end();
 
 
//  bool status = qi::parse(beg, end, grammar, ds);



 return 0;
}

