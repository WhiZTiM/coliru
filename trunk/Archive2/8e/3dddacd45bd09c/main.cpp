#include<iostream>
#include <thread>
int x = 0;
int nVueltas = 1000000;
void hola(){
std::cout <<"Hola Mundo...";
for(int i=0; i<nVueltas; i++)x++;
}
void adios(){
std::cout <<"Spock dice: larga vida y prosperidad...";
for(int i=0; i<nVueltas; i++){
    std::cout <<"Ssadaadds"<<std::endl;
    int x=2*x;
}
}
int main(){
std::thread h(hola);
std::thread i(hola);
std::thread j(adios);
h.join();
i.join();
j.join();
std::cout << x;
}