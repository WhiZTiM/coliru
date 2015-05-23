#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s1 = "abcd";
    string s2 = "abc";
    
    int s1len = s1.length();
    int s2len = s2.length();
    
    for (int i = 0; i <= s2len - s1len; i++) {
        // it will never calls (as expected, since 3 - 4 = -1)
    }
    
    for (int i = 0; i <= s2.length() - s1.length(); i++) {
        // it calls once (which is strange)
    }
}