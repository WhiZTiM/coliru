#include<iostream>
using namespace std;
int main()
{
        int a[3]={1,2,3};
        //cout << *(a+2) << endl;
        cout << *(&a[2]) << endl;
        cout << (int*)(&a[2]) << endl;
        cout << &a[2] << endl;
        cout <<static_cast<int*>( &a[2]) << endl;
}