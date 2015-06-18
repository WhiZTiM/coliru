#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
// Demande le mot et l'affiche
   cout << "saisissez un mot" << endl;
   string motMys;
   std::cin >> motMys;
   std::cout << motMys; 
//melange des lettres

//boucle
string rep;
while (rep!=motMys)
{
    std::cout << "quel est ce mot ?" << endl;
    std::cin >> rep;
    
if (rep==motMys)
    {std::cout << "bravo" << endl;}
    
else 
    {std::cout << "ce n'est pas sa" << endl; }
}
}