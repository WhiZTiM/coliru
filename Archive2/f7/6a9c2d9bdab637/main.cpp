#include <boost/spirit/include/classic.hpp>
#include <boost/spirit/include/phoenix1.hpp>

#include <iostream>

int main()
{
    int variable = 123;
	
	using namespace boost::spirit::classic;
	using namespace phoenix;

    // this is expected to assign 0 to 'variable'.
	rule<> testRule =
            int_p [assign_a( variable, 0)]
		;	
	
	parse_info<> result = parse( "321", testRule );
	
	if ( result.hit )
    {
		std::cout << "result: " << variable << '\n';
    }
    else
    {
        std::cout << "parsing failed\n";
    }
	
	return 0;
}