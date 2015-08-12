#include <iostream>
#include <string>

using namespace std;

int main()
{
    int age1;
    int age2;
    string name1;
    string name2;

cout << "Please enter the name for one people: " << "\n";
getline (cin, name1);
cout << "Please enter the age for this people: " << "\n";
cin >> age1 >> ws;

cout << "Please enter the name for another people: " << "\n";
getline (cin, name2);
cout << "Please enter the age for this people too: " << "\n";
cin >> age2 >> ws;

if ( (age1 <= 100 || age2 <= 100) && (age1 < age2) )
{
    cout << name1 << " is younger!" << "\n";
}
else if ( (age1 <= 100 || age2 <= 100) && (age1 > age2) )
{
    cout << name2 << " is younder!" << "\n";
}
else if ( (age1 <= 100 || age2 <= 100) && (age1 = age2) )
{
    cout << name1 << " and " << name2 << " are of the same age!" << "\n";
}
else
{
    cout << "You've got some really old people that are well older than 100!";
}
}