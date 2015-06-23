#include<iostream>

// "Fuck, I'm Downed" "Alright, here comes Johnny!" "Diamn... where are you?" 

// find 2nd word and 4th word -> example: i'm(3), NULL | here(4), Johnny(6) ... 


// znaleźć początek słowa, zliczanie go, wypisanie;
// unikać separatorów
// jeżeli separator-> ignoruj znak


int main(int argc, char** argv) 
{    
    using namespace std;
    int ret = 0;

    char separators[] =" !?,.;:\t";
    char endOfString ='\0';
    
    char sentence1[] ="Fuck, I'm Downed";
    char sentence2[] ="Alright, here comes Johnny!";
    char sentence3[] ="Diamn... where are you?";

    char* strPtr;
    char* strEnd;

strPtr = sentence1;
std::cout<< strPtr;

}


/*

początek - > x;
koniec -> y

zliczanie od początku do końca + długość'
__________________________________________

początek.... wypisywanie i zliczanie ,jeżeli koniec to długość


*/

