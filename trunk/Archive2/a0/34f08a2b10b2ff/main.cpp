#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char* argv[])
{
    std::vector<bool> example;
    po::options_description desc("options");
    desc.add_options()
        ("example,e",
         po::value(&example)
         ->default_value(std::vector<bool>(), "false")
         ->implicit_value(std::vector<bool>(1), "true")
         ->zero_tokens()
        );
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    std::cout << example.size() << std::endl;
}