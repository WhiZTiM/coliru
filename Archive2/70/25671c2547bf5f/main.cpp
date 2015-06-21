#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int main(){

    char num[10];
    fstream file;
    file.open("text.txt", ios::trunc|ios::in|ios::out| ios::binary);
    if (!file)
    {
        cerr << "File could not be opened" << endl;
        exit(1);
    } // End if

    for (int i = 0; i <= 5; i++){
        cout << "Enter an integer " << endl;
        cin >> num[i];        //Input a number
    }
    // write the array once and outside of the loop
    file.write((char*)num, sizeof(num)); 

    // not necessary - just to ensure we read numbers in the next lines
    memset(num, 0, sizeof(num)); 
    // go to the beginning of the file
    file.seekg(0);
    // read the array once and outside of the loop
    file.read((char*)num, sizeof(num));

    for (int i = 0; i <= 5; i++){
        cout << endl << num[i] << ", ";
    }

    file.close();
  //  system("pause");
}