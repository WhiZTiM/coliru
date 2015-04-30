#include <iostream>
using namespace std;
int main()
    {
int contadora=1;
int n;
int topone;
int numblisten;
    cin >> n;

    topone= -1;
    while(n >= contadora){


    cin >>numblisten;
    if(topone<numblisten){
       topone=numblisten;


    }
contadora=contadora+1;



}
cout << topone;


 return 0;
}
