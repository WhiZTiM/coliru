#include <iostream>
#include <fstream>
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
        file.write((char*)num, sizeof(num));  //Function write to write data to file
    }

    for (int i = 0; i <= 5; i++){
        file.read((char*)num, sizeof(num));  //Function to read data from the file
        cout << endl << num[i] << " ";
    }
    file.close();
  //  system("pause");
}