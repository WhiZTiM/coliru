#include <iostream>
using namespace std;
int main()
    {

  int N;
  int S;
  int base;
  int contadora=0;
  int Msaldo;
  cin >> N >> S;
  base= S;
  Msaldo=S;
  while (contadora < N ){
    cout << "saldo = \n" << base <<endl;
     cin >> S;
     base = base + S;
     cout << "saldo = \n" << base << endl;
     if(Msaldo < base){

        Msaldo = base;
        cout << "saldo = \n" << Msaldo << endl;
     }

  contadora++;

  }
 cout << Msaldo;








 return 0;
}
