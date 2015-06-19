#include <string>
#include <iostream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int ac, char* const av[])
{
    double sizeFactor;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "produce help message")
		("size-factor,s", po::value<double>(&sizeFactor)->default_value(2.0), "set size factor of processing.")
		("input-path,i", po::value< std::string >(), "input path");

	po::variables_map vm;
	po::store(po::parse_command_line(ac, av, desc), vm);
	po::notify(vm);

    std::cout << sizeFactor << std::endl;
	return 0;
}