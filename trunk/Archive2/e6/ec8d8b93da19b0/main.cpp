#include <iostream>
struct nodo{int info; nodo* next; nodo(int a=0, nodo* b=0){info=a; next=b;}};
using namespace std;
nodo* crea(int dim)
{
    if(!dim)
        return 0;
    else{
        int x;
        cin>>x;
    return new nodo(x,crea(dim-1));
    }
        
}
void stampa(nodo* L)
{
    if(L)
    cout<<L->info<<' ';
    stampa(L->next);
}
int main()
{
  int dim;
  cin>>dim;
  nodo*L=crea(dim);
  stampa(L);
}