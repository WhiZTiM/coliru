#include <iostream>
using namespace std;

int main()
{
    float somma,diff,prodotto,divisione,num1,num2;
    int scelta;
    cout<<endl;
    cout<<endl;
    cout<<"Benvenuto, questa e' una calcolatrice fatta da me :)"<<endl;
    cout<<"Scegli l'operazione che desideri svolgere"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"\t""somma <1>"<<"\t""differenza <2>"<<"\t"<<"\t""prodotto <3>"<<"\t""divisione <4>"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;
    
    cin>>scelta;
    
    cout<<endl;
    cout<<endl;
    
     switch(scelta)
               {
                             case 1:      
                                          cout<<"bene...ora puoi inserire i numeri e premere invio fra un numero e l'altro"<<endl;
                                          cout<<endl;
                                          cout<<endl;
                                          cin>>num1;
                                          cin>>num2;
                                          somma=num1+num2;
                                          cout<<endl;
                                          cout<<"La somma e'"<<somma<<endl;
                                          break;
                             case 2:
                                          cout<<"bene...ora puoi inserire i numeri e premere invio fra un numero e l'altro"<<endl;
                                          cout<<endl;
                                          cout<<endl;
                                          cin>>num1;
                                          cin>>num2;
                                          diff=num1-num2;
                                          cout<<endl;
                                          cout<<"La differenza e'"<<diff<<endl;
                                          break;
                             case 3:
                
                                          cout<<"bene...ora puoi inserire i numeri e premere invio fra un numero e l'altro"<<endl;
                                          cout<<endl;
                                          cout<<endl;
                                          cin>>num1;
                                          cin>>num2;
                                          if(num1==0 or num2==0)
                                          {
                                                     cout<<endl;
                                                     cout<<"ERROR"<<endl;
                                                     }
                                          else
                                          {
                                                     prodotto=num1*num2;
                                                     cout<<endl;
                                                     cout<<"Il prodotto e'"<<prodotto<<endl;
                                                     }
                                          break;
                             case 4:
                
                                          cout<<"bene...ora puoi inserire i numeri e premere invio fra un numero e l'altro"<<endl;
                                          cout<<endl;
                                          cout<<endl;
                                          cin>>num1;
                                          cin>>num2;
                
                                          if(num1==0 or num2==0)
                                          {
                                                     cout<<endl;
                                                     cout<<"ERROR"<<endl;
                                                     }
                                          else
                                          {
                                                     divisione=num1/num2;
                                                     cout<<endl;
                                                     cout<<"La divisione e'"<<divisione<<endl;
                                                     }
                                          break;
                       
                            default:
                                          cout<<endl;
                                          cout<<"numero non presente";
               }
    
    cout<<endl;
    cout<<endl;
    
    system("pause");
    return 0;
}
    

