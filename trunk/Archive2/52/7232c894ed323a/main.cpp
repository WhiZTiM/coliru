#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

struct counter { int count = 0; };
void validate(boost::any& v, std::vector<std::string> const& xs, counter*, long)
{
    if (v.empty()) v = counter{1};
    else ++boost::any_cast<counter&>(v).count;
}

int main(int argc, char* argv[])
{
    counter example;
    po::options_description desc("options");
    desc.add_options()
        ("example,e",
         po::value(&example)
         ->zero_tokens()
        );
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    std::cout << example.count << std::endl;
}