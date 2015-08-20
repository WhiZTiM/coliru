#include<iostream>
#include<exception>
using namespace std;
class MyException:public exception
{
   public:
  const char*  what()const throw()
   {
        
       return "Error";
   }
};
int main()
{
   try{
       
        throw MyException();
       
       }  
       catch(MyException&s)
       {
             cout<<s.what()<<endl;
        }
      catch(...)//catching object of MyException here by reference//it would accept all type of exception
      {
          cout<<"catch here "<<endl;
         // cout<<what()<<endl;
      }
}