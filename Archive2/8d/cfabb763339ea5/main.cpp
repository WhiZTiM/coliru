#include <iostream>
#include <bitset>

using namespace std;

int main(void){

    const unsigned long int n = 1e2;
    
    // store (n * 2 bytes)
    unsigned short birthdays[n];
    
    static_assert( sizeof(short) == 2, "failure." );
    
    // user input
    int day = 31;   // requirement: 5 bits
    int month = 12;  // requirement: 4 bits
    int year = 127; // requirement: 7 bits. actual year = 1940(starting year) + 127 = 2067 (max year)
    
    // store
    birthdays[0] = day + (month << 5) + (year << 9);

    // how it looks
    std::bitset<16> binary(birthdays[0]);
    cout << "raw record: " << birthdays[0] << " (binary view = " << binary << ")" << endl;

    // retrieve
    day = (unsigned short)(birthdays[0] << 11) >> 11;
    month = (unsigned short)(birthdays[0] << 7) >> 12;
    year = (birthdays[0] >> 9) + 1940;
    
    cout << "day = " << day << endl;
    cout << "month = " << month << endl;
    cout << "year = " << year << endl;
}