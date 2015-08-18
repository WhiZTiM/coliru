#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main()
{
    
    int x, *p;
    x = 10;
    p = &x;
    cout << "original value: " << x << endl;
    cout << "enter value" << endl;
    int value =25;
    *p = value;
    cout << "new value" << endl;
    cout << x << endl;
    cout << p << endl;
    cout << *p << endl;
    cout << add(p,x) << endl;

}


public add(int *x, int y){
    return x + y;
}    
