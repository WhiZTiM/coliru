#include<iostream>
#include<string>
using namespace std;
const int ns=20;
const int nm=8;
int main()

{
    string nome;
    int cm; cs;
    float voto;
    float sommas,sommam,ms,mc;
     sommas=0;
    for(cs=0;cs<ns;cs++)
    {   com=0;
        sommas=0;
        cout<<"inserire il nome dello studente"<<cs+1<<"\t";
        cin>>nome;
        for(cs=0;cm<nm;cs++)
        {cout<<"inserire il voto"cm+1<<"\t";
        cin>>voto;
        sommas=sommas+voto;
        com++; 
    }
ms=sommas/nm;
cout<<endl<<"media dei voti di"<<nome<<"<<ms<<endl<<endl;
sommam=sommam+ms;
}
mc=sommam/ns;
cout<<endl<<"media dei voti della classe="<<mc<<endl;
return(0);
}