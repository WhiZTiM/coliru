#include <utility>
#include <iostream>
using namespace std;
 
int main()
{
    pair<int, double> p(2, 3.14);    //Une paire contenant un entier valant 2 et un nombre à virgule valant 3.14
 
    cout << "La paire vaut (" << p.first << ", " << p.second << ")" << endl;
 
    return 0;
}