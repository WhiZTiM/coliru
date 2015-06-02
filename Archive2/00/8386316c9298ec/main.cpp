#include <iostream>
#include <map>
#include <sstream>
#include <cstdio>

using namespace std;

map<unsigned long long int, unsigned long long int> a;

unsigned long long int dp(unsigned long long int n)
{   
   if (a.find(n) == a.end())
      a[n] = dp(n/2) + dp(n/3) + dp(n/4);

   return a[n];
}

int main()
{
    for (unsigned long long int i = 1; i <= 24; i++) {
        a[i] = i;
        if (i == 12 || i == 24)
           a[i] = i + 1;
    }
    
    std::stringstream ss;
    ss << "12 2";
    
    unsigned long long int n = 0;
    cin >> n;

    while (!feof(stdin)) {
        printf("%llu\n", dp(n));
        cin >> n;
    }
}