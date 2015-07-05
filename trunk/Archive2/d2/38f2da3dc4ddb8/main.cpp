#include <iostream>
using namespace std; 
int main()
{
    int num1 , num2;

    cout<< " Enter number 1 and number 2 \n";
    cin>> num1 >> num2;

    if (num1 == num2)
        cout<< "The both numbers are equal \n";
    else if (num1> num2)
        cout<< "Number 1 is greater than number 2 \n";
    else if (num1< num2)
        cout<< "Number 2 is greater than number 1 \n";  
    return 0;
}