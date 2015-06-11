/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  This sample demontrates a parser for a comma separated list of numbers.
//  No actions.
//
//  [ JDG May 10, 2002 ]    spirit1
//  [ JDG March 24, 2007 ]  spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace {
    template <typename Iterator>
    bool parseAliasDirective(Iterator first, Iterator last){ 
        namespace qi = boost::spirit::qi;
        namespace ascii = boost::spirit::ascii;
    
        using qi::lexeme;
        using ascii::char_;
        using qi::phrase_parse;
        using qi::lit;
        using ascii::space;
    
        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];
        
        qi::rule<Iterator, std::string(), ascii::space_type> token;
        token %= lexeme[+(char_ - space)];
        
        auto identifier = [](const std::string& s){std::cout << "identifier: " << s << std::endl;};
        auto literal = [](const std::string& s){std::cout << "literal: " << s << std::endl;};

        bool r = phrase_parse(
            first,                          /*< start iterator >*/
            last,                           /*< end iterator >*/
            lit("alias") >> token >> lit("=") >> ( quoted_string[literal] | token[identifier] ),   /*< the parser >*/
            space                           /*< the skip-parser >*/
        );
        if (first != last) // fail if we did not get a full match
            return false;
        return r;
    }
}

////////////////////////////////////////////////////////////////////////////
//  Main program
////////////////////////////////////////////////////////////////////////////
int
main()
{
    std::vector<std::string> lines = {"1aaa",
        "alias",
        "alias filename",
        "alias filename = file.name",
        "alias indexname = \"my index name\""};
        
    for(const auto& line : lines){
        std::cout << "-------------------------\n";
        std::cout << line << std::endl;
        
        if (parseAliasDirective(line.begin(), line.end()))
        {
            std::cout << "Parsing succeeded\n";
        }
        else
        {
            std::cout << "Parsing failed\n";
        }
    }
    return 0;
}
