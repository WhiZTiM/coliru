#include <iostream>
/*#include <string>
#include <vector>*/
#include <string.h>
#include <stdlib.h>
#include <assert.h>
/*
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}*/

int isspace(char *s){
    return false;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

char* Question1(int n,  char* inputString){
    //+32 => higher to lower
    //-32 => lower to higher
    // A = 65
    // Z = 90
    // a = 97
    // z = 122
    // 0 = 48
    // 9 = 57
    //inputString = trim(inputString); // does not work
    int l = strlen(inputString);
    int size = l;
    for(int i=0;i<l;i++){
        if(inputString[i] == ' '){
            size--;
        }
    }
    int decalage = 0;
    char *result = (char*)malloc(size*sizeof(char)+1);
    for(int i=0;i<size;i++){
        if(inputString[i] == ' '){
            decalage++;
        }
        else{
            int majOuMin = 0;
            if('A' <= inputString[i] && inputString[i] <= 'Z'){
                majOuMin = 32 + n;
            }
            if('a' <= inputString[i] && inputString[i] <= 'z'){
                majOuMin = -32 + n;
            }
            result[i-decalage] = (char)(inputString[i] + majOuMin);
            
        }
    }
    //printf(l,%n);
    //std::cout << 5 << std::end;
    
    //char *result = malloc(sizeof(char)*(strlen(inputString)))
    return result;
}

int main()
{
    
    char *p = "J'aime la programmation! ";
    char *q = Question1(3,p);
    std::cout << q << std::endl;
    //std::cout << Question1(0,p) << std::endl;
}