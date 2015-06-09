#include <iostream>
#include <string>

using namespace std;

int main()
{
    unsigned char a[10]={'0','1','2','3','4','5','6','7','8','9'}; // 1
        string b="5";
        if(a[5]==b[0]){ // 2
               cout<<"true"<<endl; // 3
    }
    return 0;
}
