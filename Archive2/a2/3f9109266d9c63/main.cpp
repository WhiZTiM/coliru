#include <iostream>
#include <string>
#include <vector>

using namespace std;


int rand3(){ //0,1,2
    int res;
    for (int i = 0; i < 6; i++){
        res += rand() * 2;
    }
    return res / 2;
}

int main()
{
   int i0, i1, i2;
    
   for(int i = 0; i < 1e3; i++){
        switch(rand3()){
            case 0:
            i0++;
            break;
            case 1:
            i1++;
            break;
            case 2:
            i2++;
            break;
        }
   }
   cout << "0: " << i0 << endl;
   cout << "1: " << i1 << endl;
   cout << "2: " << i2 << endl;
   
   return 0;
}
