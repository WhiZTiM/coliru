#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <memory>
#include <map>
#include <list>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <fstream>
#include <condition_variable>

using namespace std;

template<class T>
int to_int(const T& t)
{
    std::stringstream s(t);
    int i;
    s >> i;
    if (s.fail())
        throw invalid_argument("Unable to convert to int in to_int()");

    return i;
}

int extract(const std::string& line) try
{
    int x;
    x = to_int(line);
    return x;
}
catch (const invalid_argument& e) { cout << e.what(); throw; }

int main()// try
{
    to_int("abc");

    return 0;
}
//catch (const exception& e)
//{
////    cout << e.what();
//    cin.get();
//}