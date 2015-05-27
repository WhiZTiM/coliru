#include <iostream>

using namespace std;

int main() {
    int n,count=0;
    cout<<"enter a integer: ";
    cin>>n;
    
    while(n!=0)
    {
        n/=10;
        ++count;
    }
    cout>>"number of digits :"<<count
}