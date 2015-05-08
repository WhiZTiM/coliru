//http://stackoverflow.com/questions/30117024/getting-opposite-results-when-using-indices-for-bitset
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

int main()
{
    char c = 'C';
    bitset<7> b(c);
    cout << b << endl;
    for(int j = 0; j<7;++j){
           cout<<b[7-j];
    }
    cout << '\n';
}