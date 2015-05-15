#include <iostream>
#include <string>
using std::cout;
using std::string;
template<class C>
C min(C a,C b) {
    return a<b?a:b;
}
int main()
{
    string a="first string";
    string b="second string";
    cout<<"minimum string is: "<<min(a,b)<<'\n';
    int c=3,d=5;
    cout<<"minimum number is: "<<min(c,d)<<'\n';
    double e{3.3},f{6.6};
    cout<<"minimum number is: "<<min(e,f)<<'\n';
    char g{'a'},h{'b'};
    cout<<"minimum number is: "<<min(g,h)<<'\n';
    return 0;
}