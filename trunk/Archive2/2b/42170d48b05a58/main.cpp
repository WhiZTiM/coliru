#include <iostream>
#include<cmath>//pour pouvoir utiliser les fonctions mathématiques
using namespace std;

int main(){
  int a(5), b(3);

  double nombre(16);
  double const racineCarre(sqrt(nombre));
  cout<<"la racine carrée de nombre est: "<<racineCarre<<endl;
  int const alfa=pow(a,b);//calcul 2 puissance 3 qui est 8
  cout<<"la valeur de a puissance b est: "<<alfa;
  
  return 0;
}