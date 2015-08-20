#include <iostream>

using namespace std;

void cleanStringDots(string& str){
    for (int i=0;i<str.size()-1;i++){
      if (str[i] == '.' && str[i+1] == '.'){
           size_t count = 1;
           for (int j = i+2; j<str.size()-1 && str[j] =='.';j++){
               if (str[j]=='.') {
                  count++; 
                  }  
             }
             str.erase(i+1,count);
        }
    }    
}

int main(){
string str = "temp.temp2..temp3....temp4......temp5";
cleanStringDots(str);
cout<<str;
}