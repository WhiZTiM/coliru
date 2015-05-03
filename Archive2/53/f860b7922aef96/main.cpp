#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

template<class T>
int to_int(const T& t)
{
    std::stringstream s(t);
    int i;
    s >> i;
    if (s.fail()) throw invalid_argument("to_int() was unable to convert its argument.");

    return i;
}

int extract(const std::string& line) try
{
    return to_int(line);
}
catch (const invalid_argument& e) { cout << "Invalid pragma line" + line << endl; throw; }

int main() try
{
    extract("pragma line");

    return 0;
}
catch (const invalid_argument& e) { cout << e.what();}