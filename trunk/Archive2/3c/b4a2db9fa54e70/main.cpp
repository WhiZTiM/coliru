#include <map>
#include <iostream>
#include <string>

void foo(const std::string& str) 
{
    std::map<std::string, int> M;
    for(int i=0;str[i];i++)
    {

        char temp[5001];
        int k=0;
        std::cout << str[i] << std::endl;
        for(int j=i;str[j];j++)
            {
                temp[k]=(char)str[j];
                k++;
                temp[k]='\0';
                std::string e(temp);
                M[e]++;
                std::cout << j << std::endl;
            }
    }
    
    // display results
    for ( auto pair : M) {
        std::cout << pair.first << " - " << pair.second << std::endl;  
    }
}

int main(int argc, char** argv)
{
    foo("abababababa");
    std::cout << "OK" << std::endl;
}