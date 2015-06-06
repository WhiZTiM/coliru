#include <iostream>
#include <regex>
#include <iterator>
#include <string>
using namespace std;



int main()
{
    string str ="abceda cdabc ytabc";
    regex e("(a)b(c)");
    sregex_iterator pos(str.cbegin(),str.cend(),e);
    sregex_iterator end;
    for(; pos!=end; pos++)
    {
        cout<<pos->str()<<endl;
    }
    return 0;
}
