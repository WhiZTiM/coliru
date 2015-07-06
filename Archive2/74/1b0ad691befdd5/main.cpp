#include <iostream>
#include <fstream>
#include <iterator>
#include <set>

using namespace std;

set<long> read_file(string const& fname) {
    ifstream file(fname);
    return set<long>(istream_iterator<long>(file), {});
}

int main() 
{
    auto const set1 = read_file("myfile1.txt");
    auto const set2 = read_file("myfile2.txt");

    for (auto l : set1)
    {
        auto match = set2.find(l);
        if (match == set2.end())
            cout << "There is no match for " << l << " in the second file\n";
        else
            cout << l << " is in both files\n";
    }
}
