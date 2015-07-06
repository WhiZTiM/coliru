#include <iostream>
#include <fstream>
#include <iterator>
#include <set>

using namespace std;

set<long> read_file(string const& fname) {
    ifstream file(fname.c_str());
    istream_iterator<long> b(file), e;
    return set<long>(b, e);
}

int main() 
{
    set<long> const set1 = read_file("myfile1.txt");
    set<long> const set2 = read_file("myfile2.txt");

    typedef set<long>::const_iterator It;

    for (It it = set1.begin(); it!=set1.end(); ++it)
    {
        It match = set2.find(*it);
        if (match == set2.end())
            cout << "There is no match for " << *it << " in the second file\n";
        else
            cout << *it << " is in both files\n";
    }
}
