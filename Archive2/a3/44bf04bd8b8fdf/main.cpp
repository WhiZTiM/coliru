// Nick
// Stars
// Sources:
// This will print patterns of stars.

#include <iostream>
using namespace std;

int main() {
    // print a line of 10 stars
    for (int count = 0; count < 10; count++) {
        cout << "*";
    }
    cout << endl << endl;
    
    // print a filled 4x4 square of stars
    for (int count = 0; count < 4; count++) {
        cout << "****" << endl;
    }
    cout << endl << endl;
    
    // print a filled 4x4 square of stars
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl << endl;
    
    // print a filled 4x4 triangle of stars
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < row+1; col++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl << endl;
    
    // print a filled 4x4 upside-down triangle of stars
    for (int row = 4; row > 0; row--) {
        for (int col = 0; col < row; col++) {
            cout << "*";
        }
        cout << endl;
    }
    cout << endl << endl;
    
    // print a filled 4x4 checkerboard of stars
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (row%2 == col%2) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
    
    // pause and exit
    getchar();
    return 0;
}