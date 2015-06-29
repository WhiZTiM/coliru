#include <boost/progress.hpp>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char** argv)
{
    std::ifstream myFile(argv[1], std::ifstream::in);
    std::string line;
    std::vector<std::string> identVector;

    while (std::getline(myFile, line))
    {
        identVector.push_back(line);
    }

    std::unordered_set<std::string> myStringSet;

    boost::progress_timer timer; //start benchmarking there

    for (std::vector<std::string>::const_iterator it = identVector.begin();
         it != identVector.end(); it++)
    {
        myStringSet.insert(*it);
    }

    return 0;
}