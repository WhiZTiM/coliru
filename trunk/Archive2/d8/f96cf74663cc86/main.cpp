#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>
namespace qi  = boost::spirit::qi;

int main() 
{
    qi::int_parser<uintmax_t, 16> hex_int;
	std::vector<uintmax_t> v_BF_Char ;
	std::vector<uintmax_t> v_Begin_BF_Range ;
    typedef std::string::const_iterator It;

    std::string const line = "<005F> <0061> <0031> <0071> [<00623> <006111>]";

    It str_line = line.begin(), l = line.end();

    
    qi::rule<It, uintmax_t()> braced_hex = '<' >> hex_int >> '>';
   // BOOST_SPIRIT_DEBUG_NODE(braced_hex);

	bool check1 = qi::phrase_parse(str_line, l, *braced_hex , qi::space, v_BF_Char);
	bool check2 = qi::phrase_parse(str_line, l, *braced_hex >> '[' >> *braced_hex >> ']' , qi::space, v_Begin_BF_Range);
	
	std::cout << "Extraction from special Case is: " << v_Begin_BF_Range.size() << "\n";	
	for (size_t n = 0; n < v_Begin_BF_Range.size(); n++)
	{
		std::cout << v_Begin_BF_Range[ n ] << " ";
	}

	std::cout << "\n\nExtraction from Simple Case is: " << v_BF_Char.size() << "\n";	
	for (size_t n = 0; n < v_BF_Char.size(); n++)
	{
		std::cout << v_BF_Char[ n ] << " ";
	}



if (str_line!=l) 
{
std::cout << "Remaining unparsed: '" << std::string(str_line,l) << "'\n";
}

}