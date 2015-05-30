    	#include <vector>
 		#include <sstream>
		#include <iostream>
 		#include <boost/spirit/include/qi.hpp>
		#include <boost/spirit/include/qi_match.hpp>
		#include <boost/fusion/include/io.hpp>

		using type = boost::fusion::vector<char, int, int>;

		int main() {
			std::istringstream istr{
				"***: @a_-091"
				"**: @aa_-037_-036"
			};

			std::vector<type> data;

			namespace qi = boost::spirit::qi;
			istr >> std::noskipws >> qi::match(*(
				*qi::omit[qi::char_ - '@'] >> '@' >> qi::char_ >> (
					'_' >> qi::int_ >> qi::attr(0) |
					qi::omit[qi::char_] >> '_' >> qi::int_ >> '_' >> qi::int_)
				), data);

			for (size_t i = 0; i != data.size(); ++i) {
				std::cout << data[i] << "\n";
			}

			return 0;
		}