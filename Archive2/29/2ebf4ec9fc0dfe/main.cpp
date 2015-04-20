#include <iostream>

using namespace std;

int cookBook();

int main()
{
int cookBook();
return 0;
}

int cookBook(){

int choice{}; //store selection here

cout << "Your electronic cookbook is at your service." << endl;
cout << "You can choose from the following dishes:" << endl;
cout << "1: Eggs" << endl;
cout << "2: Fish" << endl;
cout << "3: poop" << endl;
cout << "4: pee" << endl;
cout << "Enter your number: " << endl;
cin >> choice;

switch (choice){
case 1: cout << "You have chosen Eggs!" << endl;
    break;
case 2: cout << "You have chosen fish!" << endl;
    break;
case 3: cout << "You have chosen poo. WTF?!" << endl;
    break;
case 4: cout << "You drink...pee?" << endl;
    break;
default: cout << "You dont eat anything you weirdo!" << endl;
    break;

}
return 0;
}