#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>

struct geo_data_t
{
    std::vector<double> time;
	std::vector<int> checksum;
	std::vector<std::string> mid;
	double uLeftLat;
	double uLeftLon;
	double bRightLat;
	double bRightLon;

	geo_data_t():uLeftLat(0.0), uLeftLon(0.0), bRightLat(0.0), bRightLon(0.0) {time.resize(0); checksum.resize(0); mid.resize(0); }
};


bool parse_geo_data(std::string &input, geo_data_t &data)
{
	using namespace boost::spirit;

	std::string::iterator first = input.begin();
	std::string::iterator last = input.end();

	qi::rule<std::string::iterator, std::vector<double>(), ascii::space_type> time_rule;
	qi::rule<std::string::iterator, std::vector<int>(), ascii::space_type> checksum_rule;
	qi::rule<std::string::iterator, std::vector<double>(), ascii::space_type> coordinates_rule;
	qi::rule<std::string::iterator, std::vector<std::string>(), ascii::space_type> mid_rule;

	//Time field has one double followed by an optional double
	time_rule = qi::lit("time") >> '=' >> qi::double_ >> -(qi::lit(',') >> qi::double_ );
	//Checksum field has one int followed by an optional int
	checksum_rule = qi::lit("checksum") >> '=' >> qi::int_  >> -(qi::lit(',') >> qi::int_ );
	//Coordinates field has four doubles interleaved between a set of different literals 
	coordinates_rule = qi::lit("uLeftLat") >> '=' >> qi::double_ >> ',' >> qi::lit("uLeftLon") >> '=' >> qi::double_ >> ',' >> qi::lit("bRightLat") >> '=' >> qi::double_ >> ',' >> qi::lit("bRightLon") >> '=' >> qi::double_ ;
	//Mid field has a list of string seperated by a literal
	mid_rule = qi::lit("mid") >> '=' >> *(qi::char_ - qi::lit("%20")) % qi::lit("%20");
	
	//Use a temp vector to store the attribute synthesised from coordinates_rule
	std::vector<double> coords;

	bool parser_status = qi::phrase_parse( first, last,  
										*(time_rule >> '&')				//Input can have zero or more time rules
										>> checksum_rule				//Input should contain only one checksum rule
										>> -('&' >> coordinates_rule)	//Input can contain zero or one coordinate rule
										>> -('&' >> mid_rule),			//Input can contain zero or one mid rule
										ascii::space, 
										data.time,
										data.checksum,
										coords,
										data.mid); 
	
	//Feed back from temp vector back to geo_data_t structure
	if(coords.size() == 4)
	{
		data.uLeftLat = coords[0]; 
		data.uLeftLon = coords[1]; 
		data.bRightLat = coords[2]; 
		data.bRightLon = coords[3]; 
	}

	if( (parser_status == false) || (first != last) )
	{	
		if(first != last)
			std::cout << "Parsing failed from location = " << std::string(first,last) << std::endl;
		else
			std::cout << "Parsing failed\n";

		return false;
	}

	return true;
}

void display(geo_data_t &geo_data)
{
	std::cout << "Time : " ;
	std::for_each(geo_data.time.begin(), geo_data.time.end(), ([](const double &val){ std::cout << val << ' ';}));
	std::cout << std::endl;

	std::cout << "Checksum : " ;
	std::for_each(geo_data.checksum.begin(), geo_data.checksum.end(), ([](const int &val){ std::cout << val << ' ';}));
	std::cout << std::endl;

	std::cout << "LeftLat : "  << geo_data.uLeftLat << std::endl;
	std::cout << "LeftLon : "  << geo_data.uLeftLon << std::endl;
	std::cout << "RightLat : "  << geo_data.bRightLat << std::endl;
	std::cout << "RightLon : "  << geo_data.bRightLon << std::endl;

	std::cout << "Mid : " ;
	std::for_each(geo_data.mid.begin(), geo_data.mid.end(), ([](const std::string &val){ std::cout << val << ' ';}));
	std::cout << std::endl;
}


int main(void)
{
	std::string input_string [] = {
		"time=10.000,21.000&checksum=100,200&uLeftLat=20.000,uLeftLon=21.000,bRightLat=21.00,bRightLon=22.000&mid=Blue%20Rain",
		"time=10.000&checksum=100,200&uLeftLat=20.000,uLeftLon=21.000,bRightLat=21.00,bRightLon=22.000&mid=Blue",
		"checksum=100&uLeftLat=20.000,uLeftLon=21.000,bRightLat=21.00,bRightLon=22.000&mid=Blue%20Rain",
		"time=10.000,21.000&checksum=100,200&mid=Blue",
		//Some negative test cases
		//3 time values
		"time=10.000,20.000,30.000&checksum=100,200&uLeftLat=20.000,uLeftLon=21.000,bRightLat=21.00,bRightLon=22.000&mid=Rain",
		//3 coordinate values
		"time=10.000&checksum=100,200,300&uLeftLat=20.000,uLeftLon=21.000,bRightLat=21.00,bRightLon=22.000&mid=Rain",
	};

	std::string::size_type const sz = sizeof ( input_string ) / sizeof ( input_string [ 0 ] ) ;
	for ( std::string::size_type odx ( 0 ); odx < sz; ++odx ) 
	{
		std::string input = input_string[odx];
		geo_data_t geo_data;

		std::cout << "--------------------------------\n";
		if(parse_geo_data(input, geo_data))
		{
			display(geo_data);
		}
		std::cout << "--------------------------------\n";
	}

}