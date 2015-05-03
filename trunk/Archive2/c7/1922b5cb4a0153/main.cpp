#include <iostream> 
using namespace std; 
const int ng=31; 
int main() 
{ 
int ngfreddi; 
int i; 
float tempo; 
ngfreddi=0; i=0; 
for(i=0;i<ng;i++) 
{ 
cout<<"inserire la temperatura del giorno"<<i+1<<"\t"; 
cin>>tempo; 
if(tempo<0) 
ngfreddi++; 
}
return(0); 
}
