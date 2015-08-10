#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;

int main(int argc, char** argv) {
    namespace fs = boost::filesystem;
	namespace po = boost::program_options;

	po::options_description desc("Example");

	int i = -99; // some value
	fs::path v;  // the only place where we ever specify the type!

	desc.add_options()
	  ("help", "Print help messages")
	  ("value,v", po::value(&i)->default_value(42),          "Input folder")
	  ("input,i", po::value(&v)->default_value("TheAnswer"), "Input folder");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	notify(vm);

	std::cout << i << ", " << v << "\n";
}
    