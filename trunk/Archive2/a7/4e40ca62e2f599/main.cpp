#include <iostream>
#include <regex>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    stringstream records("foo:abc:\nbar:123:\nbaz:478:\ntest-err:df\n\n:yadda:yadda:yadda");
    regex reg("(\\w+):(\\w+):");
    string line;
    for(int i = 1; getline(records, line); ++i)
    {
        smatch match;
        cout << i << " : \"" << line << "\"" << endl;
        if(regex_match(line, match, reg))
        {
            string field = match[1].str(),
                        value = match[2].str();
            cout << "\tField : " << field << endl;
            cout << "\tValue : " << value << endl;
        }
        else
        {
            cout << "\tInvalid record\n";
        }
    }
    return 0;
}
