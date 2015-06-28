#include <iostream>
using namespace std;

int main()
{
  float gallons, liters;

  cout << "Enter number of gallons: ";
  cin >> gallons; // Read the inputs from the user

  liters = gallons * 3.7854; // convert to liters

  cout << "Liters: " << liters << endl; 

  return 0;
}